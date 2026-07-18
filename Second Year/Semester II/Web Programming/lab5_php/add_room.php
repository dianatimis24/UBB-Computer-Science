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
    header('Location: list_rooms.php');
    exit;
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Add a Room</title>
    <link href="style.css" rel="stylesheet">
</head>
<body>
    <div class="page-wrapper--small">
        <h2 class="page-title">Add a Room</h2>

        <div class="form-group">
            <label class="form-group__label" for="roomNumberField">Room Number:</label>
            <input class="form-group__input" type="text" id="roomNumberField" placeholder="e.g. 101">
        </div>
        <div class="form-group">
            <label class="form-group__label" for="categoryField">Category:</label>
            <input class="form-group__input" type="text" id="categoryField" placeholder="e.g. standard, deluxe, suite">
        </div>
        <div class="form-group">
            <label class="form-group__label" for="typeField">Type:</label>
            <input class="form-group__input" type="text" id="typeField" placeholder="e.g. single, double, twin">
        </div>
        <div class="form-group">
            <label class="form-group__label" for="priceField">Price per night (€):</label>
            <input class="form-group__input" type="text" id="priceField" placeholder="e.g. 120.00">
        </div>
        <button id="insertLogButton" class="btn btn--primary u-mb-md">Add Room</button>

        <form method="post" class="u-mt-md">
            <input type="submit" class="btn btn--primary" name="viewAllButton" value="View all rooms">
            <input type="submit" class="btn btn--primary" name="returnButton"  value="Return to main page">
        </form>
    </div>

    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
    <script src="add_script_rooms.js"></script>
</body>
</html>