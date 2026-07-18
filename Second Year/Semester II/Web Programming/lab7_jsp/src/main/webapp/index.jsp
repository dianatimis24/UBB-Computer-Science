<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8"/>
    <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
    <title>URLCollection — Sign in</title>
    <link rel="stylesheet" href="style.css"/>
</head>
<body class="auth-page">
<div class="auth-card">
    <header class="auth-header">
        <h1 class="auth-title">URLCollection</h1>
        <p class="auth-subtitle">Your personal link collection</p>
    </header>

    <% if (request.getAttribute("error") != null) { %>
    <div class="alert alert--error"><%= request.getAttribute("error") %></div>
    <% } %>

    <form id="loginForm" method="post" action="LoginController" novalidate>
        <div class="form__group">
            <label class="form__label" for="loginUser">Username</label>
            <input class="form__input" id="loginUser" name="username" type="text"
                   required placeholder="your username" autocomplete="username"/>
            <span class="form__error" id="loginUserErr"></span>
        </div>
        <div class="form__group">
            <label class="form__label" for="loginPass">Password</label>
            <input class="form__input" id="loginPass" name="password" type="password"
                   required placeholder="••••••••" autocomplete="current-password"/>
            <span class="form__error" id="loginPassErr"></span>
        </div>
        <button class="button button--primary button--full" type="submit">Sign in</button>
    </form>

    <div class="auth-guest">
        <a href="TopController" class="auth-hint">Browse top URLs without signing in →</a>
    </div>
</div>

<script src="js/index.js"></script>

</body>
</html>