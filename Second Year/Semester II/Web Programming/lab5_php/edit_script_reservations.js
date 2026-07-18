$(document).ready(() => {
    const urlParams = new URLSearchParams(window.location.search);
    const start_date = urlParams.get('start_date');
    const end_date = urlParams.get('end_date');

    if (start_date) $('#startDate').val(start_date);
    if (end_date) $('#endDate').val(end_date);

    $('#editButton').click(() => {
        const id = parseInt(urlParams.get('id'), 10);
        const start_date = $('#startDate').val();
        const end_date = $('#endDate').val();

        if (!id || id <= 0) {
            alert("Invalid reservation ID!");
            return;
        }
        if (!start_date || !end_date) {
            alert("Please fill in both dates.");
            return;
        }
        if (start_date >= end_date) {
            alert("Start date must be before end date.");
            return;
        }

        $.ajax({
            type: "PUT",
            url: `api/reservations/${id}`,
            contentType: "application/json",
            data: JSON.stringify({ startDate: start_date, endDate: end_date }),
            success: () => {
                $('.form-group__input').val('');
                alert("Reservation edited successfully!");
            },
            error: () => alert("A network error occurred. Please try again.")
        });
    });
});