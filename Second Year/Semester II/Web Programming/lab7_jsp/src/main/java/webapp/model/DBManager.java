package webapp.model;

import webapp.domain.Url;
import webapp.domain.User;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class DBManager {
    private Connection connection;

    public DBManager() {
        connect();
    }

    public void connect() {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            this.connection = DriverManager.getConnection("jdbc:mysql://localhost/urlcollection", "root", "");
        } catch (Exception exception) {
            System.out.println("Error connecting to the database: " + exception.getMessage());
            exception.printStackTrace();
        }
    }

    public User authenticate(String username, String password) {
        User user = null;
        String query = "SELECT * FROM users WHERE username = ? AND password = ?";
        try (PreparedStatement preparedStatement = this.connection.prepareStatement(query)) {
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, password);
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    user = new User(
                            resultSet.getInt("id"),
                            resultSet.getString("username"),
                            resultSet.getString("password")
                    );
                }
            }
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }
        return user;
    }

    public List<Url> getUrlsByUser(int userId) throws SQLException {
        List<Url> urls = new ArrayList<>();
        String query = "SELECT u.id, u.url_address, u.title " +
                "FROM urls u " +
                "JOIN user_urls uu ON u.id = uu.url_id " +
                "WHERE uu.user_id = ?";
        try (PreparedStatement preparedStatement = this.connection.prepareStatement(query)) {
            preparedStatement.setInt(1, userId);
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                while (resultSet.next()) {
                    urls.add(new Url(
                            resultSet.getInt("id"),
                            resultSet.getString("url_address"),
                            resultSet.getString("title")
                    ));
                }
            }
        }
        return urls;
    }

    public List<Url> getTopUrls(int numberOfURLs) throws SQLException {
        List<Url> urls = new ArrayList<>();
        String query = "SELECT u.id, u.url_address, u.title, COUNT(uu.user_id) AS saves " +
                "FROM urls u " +
                "LEFT JOIN user_urls uu ON u.id = uu.url_id " + // LEFT JOIN to find the first n globally, even if they have 0 saves
                "GROUP BY u.id " +
                "ORDER BY saves DESC " +
                "LIMIT ?";
        try (PreparedStatement preparedStatement = this.connection.prepareStatement(query)) {
            preparedStatement.setInt(1, numberOfURLs);
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                while (resultSet.next()) {
                    urls.add(new Url(
                            resultSet.getInt("id"),
                            resultSet.getString("url_address"),
                            resultSet.getString("title"),
                            resultSet.getInt("saves")
                    ));
                }
            }
        }
//        Modificare la lab
//        String querySixthURL = "SELECT u.id, u.url_address, u.title, COUNT(uu.user_id) AS saves " +
//                "FROM urls u " +
//                "LEFT JOIN user_urls uu ON u.id = uu.url_id " + // LEFT JOIN to find the 6th globally, even if it has 0 saves
//                "GROUP BY u.id " +
//                "ORDER BY saves DESC " +
//                "LIMIT 1 OFFSET 5";
//        try (PreparedStatement preparedStatement = this.connection.prepareStatement(querySixthURL);
//             ResultSet resultSet = preparedStatement.executeQuery()) {
//            if (resultSet.next()) {
//                int sixthId = resultSet.getInt("id");
//                boolean alreadyInList = urls.stream().anyMatch(url -> url.getId() == sixthId);
//                if (!alreadyInList) {
//                    urls.add(new Url(
//                            sixthId,
//                            resultSet.getString("url_address"),
//                            resultSet.getString("title"),
//                            resultSet.getInt("saves")
//                    ));
//                }
//            }
//        }
        return urls;
    }

    public Url getUrlById(int urlId) throws SQLException {
        String query = "SELECT * FROM urls WHERE id = ?";
        try (PreparedStatement preparedStatement = this.connection.prepareStatement(query)) {
            preparedStatement.setInt(1, urlId);
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    return new Url(
                            resultSet.getInt("id"),
                            resultSet.getString("url_address"),
                            resultSet.getString("title")
                    );
                }
            }
        }
        return null;
    }

    public void addUrl(int userId, String urlAddress, String title) throws SQLException {
        int urlId = -1;
        String checkUrl = "SELECT id FROM urls WHERE url_address = ?";
        try (PreparedStatement preparedStatement = this.connection.prepareStatement(checkUrl)) {
            preparedStatement.setString(1, urlAddress);
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    urlId = resultSet.getInt("id");
                }
            }
        }

        if (urlId == -1) {
            String insertUrl = "INSERT INTO urls (url_address, title) VALUES (?, ?)";
            try (PreparedStatement preparedStatement = this.connection.prepareStatement(insertUrl, Statement.RETURN_GENERATED_KEYS)) {
                preparedStatement.setString(1, urlAddress);
                preparedStatement.setString(2, title);
                preparedStatement.executeUpdate();
                try (ResultSet keys = preparedStatement.getGeneratedKeys()) {
                    if (keys.next()) {
                        urlId = keys.getInt(1);
                    }
                }
            }
        }

        String link = "INSERT IGNORE INTO user_urls (user_id, url_id) VALUES (?, ?)";
        try (PreparedStatement preparedStatement = this.connection.prepareStatement(link)) {
            preparedStatement.setInt(1, userId);
            preparedStatement.setInt(2, urlId);
            preparedStatement.executeUpdate();
        }
    }

    public void deleteUrl(int urlId, int userId) throws SQLException {
        String query = "DELETE FROM user_urls WHERE url_id = ? AND user_id = ?";
        try (PreparedStatement preparedStatement = this.connection.prepareStatement(query)) {
            preparedStatement.setInt(1, urlId);
            preparedStatement.setInt(2, userId);
            preparedStatement.executeUpdate();
        }
    }

    public void close() {
        try {
            if (this.connection != null && !this.connection.isClosed()) {
                this.connection.close();
            }
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }
    }
}
