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
    header('Location: reservations.php');
    exit;
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Edit Reservation</title>
    <link href="style.css" rel="stylesheet">
</head>
<body>
    <div class="page-wrapper--small">
        <h2 class="page-title">Edit Reservation</h2>

        <div class="form-group">
            <label class="form-group__label" for="startDate">Start Date:</label>
            <input class="form-group__input" type="date" id="startDate">
        </div>
        <div class="form-group">
            <label class="form-group__label" for="endDate">End Date:</label>
            <input class="form-group__input" type="date" id="endDate">
        </div>
        <button id="editButton" class="btn btn--primary u-mb-md">Save Changes</button>

        <form method="post" class="u-mt-md">
            <input type="submit" class="btn btn--primary" name="viewAllButton" value="View all reservations">
            <input type="submit" class="btn btn--primary" name="returnButton"  value="Return to main page">
        </form>
    </div>

    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
    <script src="edit_script_reservations.js"></script>
</body>
</html>