<?php
require_once 'DBUtils.php';

if (!isset($_SESSION['username'])) {
    header('Location: login.php');
    exit;
}

$username = $_SESSION['username'];

?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>My Reservations</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <div class="page-wrapper">
        <h3 class="page-title">My Reservations</h3>

        <table class="data-table">
            <thead>
                <tr>
                    <th class="data-table__head-cell">ID</th>
                    <th class="data-table__head-cell">Room Number</th>
                    <th class="data-table__head-cell">Hotel Name</th>
                    <th class="data-table__head-cell">Start Date</th>
                    <th class="data-table__head-cell">End Date</th>
                    <th class="data-table__head-cell">Edit</th>
                    <th class="data-table__head-cell">Delete</th>
                </tr>
            </thead>
            <tbody>
            </tbody>
        </table>

        <div class="pagination">
            <button type="button" id="previousButton" class="btn btn--primary">Previous</button>
            <button type="button" id="nextButton" class="btn btn--primary">Next</button>
            <button type="button" id="returnButton" class="btn btn--primary">Return to main page</button>
        </div>
    </div>

    <script>var username = '<?= htmlspecialchars($username, ENT_QUOTES) ?>';</script>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
    <script src="reservations_script.js"></script>
</body>
</html>