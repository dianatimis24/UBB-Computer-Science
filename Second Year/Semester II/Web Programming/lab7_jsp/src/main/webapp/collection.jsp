<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ page import="webapp.domain.User, webapp.domain.Url, java.util.List" %>
<%
    HttpSession httpSession = request.getSession(false);
    if (httpSession == null || httpSession.getAttribute("user") == null) {
        response.sendRedirect("LoginController");
        return;
    }
    User currentUser = (User) httpSession.getAttribute("user");
    List<Url> myUrls = (List<Url>) request.getAttribute("myUrls");
    List<Url> topUrls = (List<Url>) request.getAttribute("topUrls");
    int topN = request.getAttribute("topN") != null ? (int) request.getAttribute("topN") : 10;
%>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8"/>
    <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
    <title>URLCollection — My Collection</title>
    <link rel="stylesheet" href="style.css"/>
</head>
<body>

<nav class="navbar">
    <span class="navbar__brand">URLCollection</span>
    <div class="navbar__actions">
        <span class="navbar__user"><%= currentUser.getUsername() %></span>
        <form method="post" action="LogoutController" style="display:inline">
            <button class="button button--ghost button--small" type="submit">Sign out</button>
        </form>
    </div>
</nav>

<div class="layout">
    <section class="panel">
        <div class="panel__head">
            <h2 class="panel__title">My URLs</h2>
            <button class="button button--primary button--small" onclick="openModal('addModal')">+ Add URL</button>
        </div>

        <% if (request.getAttribute("error") != null) { %>
        <div class="alert alert--error"><%= request.getAttribute("error") %></div>
        <% } %>

        <% if (myUrls == null || myUrls.isEmpty()) { %>
        <p class="empty-state">No URLs yet. Add your first one!</p>
        <% } else { %>
        <ul class="url-list">
            <% for (Url url : myUrls) { %>
            <li class="url-item">
                <div class="url-item__body">
                    <span class="url-item__title"><%= url.getTitle() %></span>
                    <span class="url-item__href"><%= url.getUrlAddress() %></span>
                </div>
                <div class="url-item__meta">
                    <button class="button button--icon" onclick="confirmDelete(event, <%= url.getId() %>)" title="Delete">✕</button>
                </div>
            </li>
            <% } %>
        </ul>
        <% } %>
    </section>

    <aside class="panel panel--aside">
        <div class="panel__head">
            <h2 class="panel__title">Top <%= topN %> URLs</h2>
        </div>

        <form class="topn-form" method="get" action="UrlController">
            <label class="form__label" for="topNInput">Show top</label>
            <input class="form__input form__input--inline" id="topNInput" name="topN"
                   type="number" min="1" max="100" value="<%= topN %>">
        </form>

        <% if (topUrls == null || topUrls.isEmpty()) { %>
        <p class="empty-state">No shared URLs yet.</p>
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
    </aside>

</div>

<div id="addModal" class="modal" role="dialog" aria-modal="true">
    <div class="modal__backdrop" onclick="closeModal('addModal')"></div>
    <div class="modal__box">
        <button class="modal__close" onclick="closeModal('addModal')">✕</button>
        <h3 class="modal__title">Add a URL</h3>
        <form method="post" action="UrlController" id="addForm" novalidate>
            <input type="hidden" name="action" value="add"/>
            <div class="form__group">
                <label class="form__label" for="addUrl">URL <span class="required">*</span></label>
                <input class="form__input" id="addUrl" name="urlAddress" type="url"
                       placeholder="https://example.com" required/>
                <span class="form__error" id="addUrlErr"></span>
            </div>
            <div class="form__group">
                <label class="form__label" for="addTitle">Title</label>
                <input class="form__input" id="addTitle" name="title" type="text"
                       placeholder="Optional display name"/>
            </div>
            <div class="modal__footer">
                <button type="button" class="button button--ghost" onclick="closeModal('addModal')">Cancel</button>
                <button type="submit" class="button button--primary">Save</button>
            </div>
        </form>
    </div>
</div>

<script src="js/collection.js"></script>

</body>
</html>