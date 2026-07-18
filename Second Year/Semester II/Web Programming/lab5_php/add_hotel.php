<?php
require_once 'DBUtils.php';

if (!isset($_SESSION['username'])) {
    header('Location: login.php');
    exit;
}
if (isset($_POST['returnButton'])) {
    header('Location: home.php');
    exit;
}
if (isset($_POST['viewAllButton'])) {
    header('Location: list_hotels.php');
    exit;
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="style.css">
    <title>Add a Hotel</title>
</head>
<body>
    <div class="page-wrapper--small">
        <h2 class="page-title">Add a Hotel</h2>

        <div class="form-group">
            <label class="form-group__label" for="nameField">Name:</label>
            <input class="form-group__input" type="text" id="nameField" placeholder="Hotel name">
        </div>
        <div class="form-group">
            <label class="form-group__label" for="addressField">Address:</label>
            <input class="form-group__input" type="text" id="addressField" placeholder="Street address">
        </div>
        <button id="insertLogButton" type="button" class="btn btn--primary u-mb-md">
            Add Hotel
        </button>

        <form method="post" class="u-mt-md">
            <input type="submit" class="btn btn--primary" name="viewAllButton" value="View all hotels">
            <input type="submit" class="btn btn--primary" name="returnButton"  value="Return to main page">
        </form>
    </div>

    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
    <script src="add_script_hotels.js"></script>
</body>
</html>
