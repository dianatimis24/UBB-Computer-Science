<?php
require_once 'DBUtils.php';

if (!isset($_SESSION['username'])) {
    header('Location: login.php');
    exit;
}

$username = $_SESSION['username'];

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
    <title>Book a Room</title>
    <link href="style.css" rel="stylesheet">
</head>
<body>
    <div class="page-wrapper--small">
        <h2 class="page-title">Book a Room</h2>

        <div class="form-group">
            <label class="form-group__label" for="startDate">Start Date:</label>
            <input class="form-group__input" type="date" id="startDate">
        </div>
        <div class="form-group">
            <label class="form-group__label" for="endDate">End Date:</label>
            <input class="form-group__input" type="date" id="endDate">
        </div>
        <button id="insertLogButton" class="btn btn--primary u-mb-md">Add Reservation</button>

        <form method="post" class="u-mt-md">
            <input type="submit" class="btn btn--primary" name="viewAllButton" value="View all reservations">
            <input type="submit" class="btn btn--primary" name="returnButton" value="Return to main page">
        </form>
    </div>

    <script>var username = '<?= htmlspecialchars($username, ENT_QUOTES) ?>';</script>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
    <script src="add_script_reservations.js"></script>
</body>
</html>