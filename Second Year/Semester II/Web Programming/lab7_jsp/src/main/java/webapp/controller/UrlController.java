package webapp.controller;

import webapp.domain.Url;
import webapp.domain.User;
import webapp.model.DBManager;

import javax.servlet.ServletException;
import javax.servlet.http.*;
import java.io.IOException;
import java.sql.SQLException;
import java.util.List;

public class UrlController extends HttpServlet {
    public static final int HTTP_UNAUTHORIZED = 401;
    public static final int HTTP_OK = 200;
    public static final int DEFAULT_NUMBER_OF_URLS = 10;

    private DBManager dbManager;

    @Override
    public void init() {
        this.dbManager = new DBManager();
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession();
        User user = (User) session.getAttribute("user");
        if (user == null) {
            response.sendError(HTTP_UNAUTHORIZED);
            return;
        }

        int topN = getTopN(request, session);

        try {
            List<Url> myUrls  = this.dbManager.getUrlsByUser(user.getId());
            List<Url> topUrls = this.dbManager.getTopUrls(topN);

            request.setAttribute("myUrls", myUrls);
            request.setAttribute("topUrls", topUrls);
            request.setAttribute("topN", topN);
            request.getRequestDispatcher("/collection.jsp").forward(request, response);
        } catch (SQLException sqlException) {
            throw new ServletException(sqlException);
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession();
        User user = (User) session.getAttribute("user");
        if (user == null) {
            response.sendError(HTTP_UNAUTHORIZED);
            return;
        }

        String urlAddress = request.getParameter("urlAddress");
        String title = request.getParameter("title");
        if (urlAddress == null || urlAddress.trim().isEmpty() ||
                (!urlAddress.trim().startsWith("http://") && !urlAddress.trim().startsWith("https://"))) {
            request.setAttribute("error", "Please enter a valid URL starting with http:// or https://");
            try {
                forwardToCollection(request, response, user);
            } catch (SQLException sqlException) {
                throw new ServletException(sqlException);
            }
            return;
        }

        if (title == null || title.trim().isEmpty()) {
            title = urlAddress.trim();
        }
        try {
            this.dbManager.addUrl(user.getId(), urlAddress.trim(), title.trim());
            response.sendRedirect("UrlController");
        } catch (SQLException sqlException) {
            throw new ServletException(sqlException);
        }
    }

    @Override
    protected void doDelete(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession();
        User user = (User) session.getAttribute("user");
        if (user == null) {
            response.sendError(HTTP_UNAUTHORIZED);
            return;
        }
        String idString = request.getParameter("id");
        try {
            if (idString != null) {
                this.dbManager.deleteUrl(Integer.parseInt(idString), user.getId());
            }
            response.setStatus(HTTP_OK);
        } catch (SQLException sqlException) {
            throw new ServletException(sqlException);
        }
    }

    private int getTopN(HttpServletRequest request, HttpSession session) {
        String topNParameter = request.getParameter("topN");
        if (topNParameter != null && !topNParameter.isEmpty()) {
            try {
                int numberOfURLs = Integer.parseInt(topNParameter);
                if (numberOfURLs >= 1 && numberOfURLs <= 100) {
                    session.setAttribute("topN", numberOfURLs);
                    return numberOfURLs;
                }
            } catch (NumberFormatException ignored) {}
        }

        Integer sessionTopN = (Integer) session.getAttribute("topN");
        return sessionTopN != null ? sessionTopN : DEFAULT_NUMBER_OF_URLS;
    }

    private void forwardToCollection(HttpServletRequest request, HttpServletResponse response, User user) throws SQLException, ServletException, IOException {
        HttpSession session = request.getSession();
        int topN = getTopN(request, session);
        List<Url> myUrls  = this.dbManager.getUrlsByUser(user.getId());
        List<Url> topUrls = this.dbManager.getTopUrls(topN);
        request.setAttribute("myUrls", myUrls);
        request.setAttribute("topUrls", topUrls);
        request.setAttribute("topN", topN);
        request.getRequestDispatcher("/collection.jsp").forward(request, response);
    }

    @Override
    public void destroy() {
        this.dbManager.close();
    }
}