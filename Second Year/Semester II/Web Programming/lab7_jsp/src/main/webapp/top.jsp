<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ page import="webapp.domain.Url, java.util.List" %>
<%
    List<Url> topUrls = (List<Url>) request.getAttribute("topUrls");
%>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8"/>
    <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
    <title>URLCollection — Top 10</title>
    <link rel="stylesheet" href="style.css"/>
</head>
<body class="auth-page">

<div class="auth-card auth-card--wide">
    <header class="auth-header">
        <h1 class="auth-title">URLCollection</h1>
        <p class="auth-subtitle">Top 10 most saved URLs</p>
    </header>

    <% if (topUrls == null || topUrls.isEmpty()) { %>
    <p class="empty-state">No URLs have been saved yet.</p>
    <% } else { %>
    <ol class="top-list">
        <% int rank = 1; for (Url url : topUrls) { %>
        <li class="top-list__item">
            <span class="top-list__rank"><%= rank++ %></span>
            <div class="top-list__body">
                <a class="top-list__link" href="<%= url.getUrlAddress() %>" target="_blank" rel="noopener"><%= url.getTitle() %></a>
                <span class="top-list__count"><%= url.getSaves() %> saves</span>
            </div>
        </li>
        <% } %>
    </ol>
    <% } %>

    <div class="auth-guest">
        <a href="LoginController" class="button button--primary">Sign in to manage your collection</a>
    </div>
</div>

</body>
</html>
