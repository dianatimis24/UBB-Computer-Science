<%@ page contentType="text/html;charset=UTF-8" language="java" isErrorPage="true" %>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8"/>
    <title>URLCollection — Error</title>
    <link rel="stylesheet" href="style.css"/>
</head>
<body class="auth-page">
<div class="auth-card">
    <header class="auth-header">
        <h1 class="auth-title">Something went wrong</h1>
    </header>
    <p class="empty-state">
        <%= exception != null ? exception.getMessage() : "An unexpected error occurred." %>
    </p>
    <div class="auth-guest">
        <a href="javascript:history.back()" class="button button--ghost">Go back</a>
        <a href="LoginController" class="button button--primary">Home</a>
    </div>
</div>
</body>
</html>