package webapp.controller;

import webapp.domain.Url;
import webapp.model.DBManager;

import javax.servlet.ServletException;
import javax.servlet.http.*;
import java.io.IOException;
import java.sql.SQLException;
import java.util.List;

public class TopController extends HttpServlet {
    public static final int DEFAULT_NUMBER_OF_URLS = 10;
    private DBManager dbManager;

    @Override
    public void init() {
        this.dbManager = new DBManager();
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try {
            List<Url> topUrls = this.dbManager.getTopUrls(DEFAULT_NUMBER_OF_URLS);
            request.setAttribute("topUrls", topUrls);
            request.getRequestDispatcher("/top.jsp").forward(request, response);
        } catch (SQLException sqlException) {
            throw new ServletException(sqlException);
        }
    }

    @Override
    public void destroy() {
        this.dbManager.close();
    }
}