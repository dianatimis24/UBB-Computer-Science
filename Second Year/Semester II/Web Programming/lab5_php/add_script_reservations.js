$(document).ready(() => {
    const urlParams = new URLSearchParams(window.location.search);
    const room_id = parseInt(urlParams.get("id"), 10);

    if (!room_id || room_id <= 0) {
        alert("No room selected. Please go back and click '+' next to a room.");
        return;
    }

    $("#insertLogButton").click(() => {
        const start_date = $("#startDate").val();
        const end_date = $("#endDate").val();

        if (!start_date || !end_date) {
            alert("Please fill in both dates.");
            return;
        }
        if (start_date >= end_date) {
            alert("Start date must be before end date.");
            return;
        }

        $.ajax({
            type: "POST",
            url: "api/reservations",
            contentType: "application/json",
            data: JSON.stringify({ roomId: room_id, startDate: start_date, endDate: end_date }),
            success: () => {
                $(".form-group__input").val("");
                alert("Reservation added successfully!");
            },
            error: (xhr) => {
                if (xhr.status === 409) {
                    alert("Room is not available for those dates.");
                } else {
                    alert("A network error occurred. Please try again.");
                }
            }
        });
    });
});