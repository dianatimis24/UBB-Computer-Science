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
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>All Hotels</title>
    <link href="style.css" rel="stylesheet">
</head>
<body>
    <div class="page-wrapper">
        <h3 class="page-title">All Hotels</h3>

        <div class="filter-bar">
            <div class="filter-bar__group">
                <label class="filter-bar__label" for="nameInputFilter">Name:</label>
                <input class="filter-bar__input" type="text" id="nameInputFilter" placeholder="Search by name">
                <button id="filterByNameButton" type="button" class="btn btn--primary">Filter</button>
            </div>
            <div class="filter-bar__group">
                <label class="filter-bar__label" for="addressInputFilter">Address:</label>
                <input class="filter-bar__input" type="text" id="addressInputFilter" placeholder="Search by address">
                <button id="filterByAddressButton" type="button" class="btn btn--primary">Filter</button>
            </div>
            <div class="filter-bar__group" style="align-self:flex-end;">
                <button id="showAllButton" type="button" class="btn btn--primary">Show All</button>
            </div>
        </div>

        <table class="data-table">
            <thead>
                <tr>
                    <th class="data-table__head-cell">ID</th>
                    <th class="data-table__head-cell">Name</th>
                    <th class="data-table__head-cell">Address</th>
                    <th class="data-table__head-cell">Add Room</th>
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
        </div>

        <form method="post" class="u-mt-md">
            <input type="submit" class="btn btn--primary" name="returnButton" value="Return to main page">
        </form>
    </div>

    <div id="editHotelModal" style="display:none; position:fixed; top:0; left:0; width:100%; height:100%;
         background:rgba(0,0,0,0.5); z-index:1000; justify-content:center; align-items:center;">
        <div style="background:#dff0d8; padding:30px; border-radius:10px; min-width:300px;">
            <h3 class="page-title">Edit Hotel</h3>
            <input type="hidden" id="editHotelId">

            <div class="form-group">
                <label class="form-group__label" for="editHotelName">Name:</label>
                <input class="form-group__input" type="text" id="editHotelName">
            </div>
            <div class="form-group">
                <label class="form-group__label" for="editHotelAddress">Address:</label>
                <input class="form-group__input" type="text" id="editHotelAddress">
            </div>

            <button id="saveHotelButton" class="btn btn--primary">Save</button>
            <button id="cancelHotelButton" class="btn btn--primary">Cancel</button>
        </div>
    </div>

    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
    <script src="hotels_script.js"></script>
</body>
</html>