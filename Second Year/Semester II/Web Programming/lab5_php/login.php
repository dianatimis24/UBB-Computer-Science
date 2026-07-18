<?php
header('Cache-Control: no-cache, must-revalidate');
require_once 'DBUtils.php';

if (isset($_SESSION['username'])) {
    header('Location: home.php');
    exit;
}

function checkValidPassword(string $username, string $password): bool
{
    $connection = new DBConnection();
    $result     = $connection->selectUserByUsername($username);
    if (count($result) === 0) return false;
    return $result[0]['password'] === $password;
}

$loginError = '';

if (isset($_POST['loginButton'])) {
    $username = trim($_POST['username'] ?? '');
    $password = trim($_POST['password'] ?? '');

    if ($username === '' || $password === '') {
        $loginError = 'Please fill in both fields.';
    } elseif (checkValidPassword($username, $password)) {
        $_SESSION['username'] = $username;
        header('Location: home.php');
        exit;
    } else {
        $loginError = 'Invalid username and/or password. Try again.';
    }
}

if (isset($_POST['indexPage'])) {
    header('Location: index.php');
    exit;
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="style.css">
    <title>Login</title>
</head>
<body>
    <form id="login-form" method="post" action="login.php" class="page-wrapper--small">
        <h2 class="page-title">Login</h2>

        <?php if ($loginError !== ''): ?>
            <p style="color:#d9534f; margin-bottom:12px;"><?= htmlspecialchars($loginError) ?></p>
        <?php endif; ?>

        <div class="form-group">
            <label class="form-group__label" for="username">Username:</label>
            <input class="form-group__input" type="text" id="username"
                   name="username" placeholder="Enter username" autocomplete="username">
        </div>
        <div class="form-group">
            <label class="form-group__label" for="password">Password:</label>
            <input class="form-group__input" type="password" id="password"
                   name="password" placeholder="Enter password" autocomplete="current-password">
        </div>

        <input type="submit" class="btn btn--primary u-mb-sm" name="loginButton" value="Login">
        <input type="submit" class="btn btn--primary" name="indexPage" value="Go to index page">
    </form>
</body>
</html>
