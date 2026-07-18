<?php
require_once 'DBUtils.php';

$loggedIn = isset($_SESSION['username']);

if (isset($_POST['returnButton'])) {
    header('Location: ' . ($loggedIn ? 'home.php' : 'index.php'));
    exit;
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>All Rooms</title>
    <link href="style.css" rel="stylesheet">
</head>
<body>
    <div class="page-wrapper">
        <h3 class="page-title">All Rooms</h3>

        <div class="filter-bar">
            <div class="filter-bar__group">
                <label class="filter-bar__label" for="categoryInputFilter">Category:</label>
                <input class="filter-bar__input" type="text" id="categoryInputFilter" placeholder="e.g. deluxe">
                <button id="filterByCategoryButton" type="button" class="btn btn--primary">Filter</button>
            </div>
            <div class="filter-bar__group">
                <label class="filter-bar__label" for="typeInputFilter">Type:</label>
                <input class="filter-bar__input" type="text" id="typeInputFilter" placeholder="e.g. double">
                <button id="filterByTypeButton" type="button" class="btn btn--primary">Filter</button>
            </div>
            <div class="filter-bar__group">
                <label class="filter-bar__label" for="priceInputFilter">Max price (€):</label>
                <input class="filter-bar__input" type="text" id="priceInputFilter" placeholder="e.g. 150">
                <button id="filterByPriceButton" type="button" class="btn btn--primary">Filter</button>
            </div>
            <div class="filter-bar__group">
                <label class="filter-bar__label" for="hotelInputFilter">Hotel:</label>
                <input class="filter-bar__input" type="text" id="hotelInputFilter" placeholder="e.g. Grand Hotel">
                <button id="filterByHotelButton" type="button" class="btn btn--primary">Filter</button>
            </div>
            <div class="filter-bar__group" style="align-self:flex-end;">
                <button id="showAllButton" type="button" class="btn btn--primary">Show All</button>
            </div>
        </div>

        <table class="data-table">
            <thead>
                <tr>
                    <th class="data-table__head-cell">Select</th>
                    <th class="data-table__head-cell">Hotel</th>
                    <th class="data-table__head-cell">Room #</th>
                    <th class="data-table__head-cell">Category</th>
                    <th class="data-table__head-cell">Type</th>
                    <th class="data-table__head-cell">Price (€)</th>
                    <?php if ($loggedIn): ?>
                    <th class="data-table__head-cell">Edit</th>
                    <th class="data-table__head-cell">Delete</th>
                    <?php endif; ?>
                </tr>
            </thead>
            <tbody>
            </tbody>
        </table>

        <div class="pagination">
            <button type="button" id="previousButton" class="btn btn--primary">Previous</button>
            <button type="button" id="nextButton" class="btn btn--primary">Next</button>
        </div>

        <div class="booking-panel">
            <h4 class="booking-panel__title">Book Selected Rooms</h4>
            <p class="booking-panel__hint">Tick one or more rooms above, pick your dates, then click Book.</p>

            <div class="filter-bar">
                <div class="filter-bar__group">
                    <label class="filter-bar__label" for="bookStartDate">Start Date:</label>
                    <input class="filter-bar__input" type="date" id="bookStartDate">
                </div>
                <div class="filter-bar__group">
                    <label class="filter-bar__label" for="bookEndDate">End Date:</label>
                    <input class="filter-bar__input" type="date" id="bookEndDate">
                </div>
                <div class="filter-bar__group" style="align-self:flex-end;">
                    <button id="bookSelectedButton" type="button" class="btn btn--primary">Book Selected</button>
                </div>
            </div>

            <p id="bookingResult" style="margin-top:10px; font-weight:bold;"></p>
        </div>

        <form method="post" class="u-mt-md">
            <input type="submit" class="btn btn--primary" name="returnButton" value="Return to main page">
        </form>
    </div>

    <?php if ($loggedIn): ?>
    <div id="editRoomModal" style="display:none; position:fixed; top:0; left:0; width:100%; height:100%;
         background:rgba(0,0,0,0.5); z-index:1000; justify-content:center; align-items:center;">
        <div style="background:#dff0d8; padding:30px; border-radius:10px; min-width:320px;">
            <h3 class="page-title">Edit Room</h3>
            <input type="hidden" id="editRoomId">

            <div class="form-group">
                <label class="form-group__label" for="editRoomNumber">Room Number:</label>
                <input class="form-group__input" type="text" id="editRoomNumber">
            </div>
            <div class="form-group">
                <label class="form-group__label" for="editCategory">Category:</label>
                <input class="form-group__input" type="text" id="editCategory">
            </div>
            <div class="form-group">
                <label class="form-group__label" for="editType">Type:</label>
                <input class="form-group__input" type="text" id="editType">
            </div>
            <div class="form-group">
                <label class="form-group__label" for="editPrice">Price (€):</label>
                <input class="form-group__input" type="text" id="editPrice">
            </div>

            <button id="saveRoomButton"   class="btn btn--primary">Save</button>
            <button id="cancelEditButton" class="btn btn--primary">Cancel</button>
        </div>
    </div>
    <?php endif; ?>

    <script>
        var userIsLoggedIn = <?= $loggedIn ? 'true' : 'false' ?>;
        var username = '<?= $loggedIn ? htmlspecialchars($_SESSION['username'], ENT_QUOTES) : '' ?>';
    </script>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
    <script src="rooms_script.js"></script>
</body>
</html>