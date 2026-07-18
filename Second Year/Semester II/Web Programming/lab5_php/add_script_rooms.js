$(document).ready(() => {
    $("#insertLogButton").click(() => {
        const urlParams = new URLSearchParams(window.location.search);
        const hotel_id = parseInt(urlParams.get("hotel_id"), 10);

        if (!hotel_id || hotel_id <= 0) {
            alert("Hotel ID is missing. Please go back and click '+' next to a hotel.");
            return;
        }

        const room_number = $("#roomNumberField").val().trim();
        if (room_number.length === 0) {
            alert("Room number cannot be empty.");
            return;
        }

        const category = $("#categoryField").val().trim();
        if (category.length === 0) {
            alert("Category cannot be empty (e.g. standard, deluxe, suite).");
            return;
        }

        const type = $("#typeField").val().trim();
        if (type.length === 0) {
            alert("Type cannot be empty (e.g. single, double, twin).");
            return;
        }

        const price = parseFloat($("#priceField").val().trim());
        if (isNaN(price) || price <= 0) {
            alert("Price must be a positive number.");
            return;
        }

        $.ajax({
            type: "POST",
            url: "api/rooms",
            contentType: "application/json",
            data: JSON.stringify({ hotelId: hotel_id, roomNumber: room_number, category, type, price }),
            success: () => {
                $(".form-group__input").val("");
                alert("Room added successfully!");
            },
            error: () => alert("Room could not be added.")
        });
    });
});