<?php
require_once 'DBUtils.php';

if (!isset($_SESSION['username'])) {
    header('Location: login.php');
    exit;
}
$username = $_SESSION['username'];

if (isset($_POST['logoutButton'])) {
    session_unset();
    session_destroy();
    header('Location: login.php');
    exit;
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Hotel Booking Site</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <main>
        <div class="page-wrapper">
            <h3 class="page-title">Welcome, <?= htmlspecialchars($username) ?>!</h3>

            <nav class="nav-bar">
                <button type="button" class="btn btn--primary"
                        onclick="location.href='list_hotels.php'">List all hotels</button>
                <button type="button" class="btn btn--primary"
                        onclick="location.href='list_rooms.php'">List all rooms</button>
                <button type="button" class="btn btn--primary"
                        onclick="location.href='list_reservations.php'">My reservations</button>
                <button type="button" class="btn btn--primary"
                        onclick="location.href='add_hotel.php'">Add hotel</button>
                <form method="post" style="display:inline;">
                    <input type="submit" class="btn btn--primary" name="logoutButton" value="Log out">
                </form>
            </nav>
        </div>
    </main>
</body>
</html>
