let currentPage = 0;
let currentUsername = "";
let allReservations = [];

const render = () => {
    const startIndex = 4 * currentPage;
    const endIndex = startIndex + 3;
    let newBody = document.createElement("tbody");

    for (let i = startIndex; i <= endIndex && i < allReservations.length; i++) {
        const res = allReservations[i];
        let newRow = newBody.insertRow();
        newRow.className = "data-table__row";

        for (let key of ["id", "room_number", "hotel_name", "start_date", "end_date"]) {
            let col = newRow.insertCell();
            col.className = "data-table__cell";
            col.appendChild(document.createTextNode(res[key] || "N/A"));
        }

        let editCol = newRow.insertCell();
        editCol.className = "data-table__cell";
        let editButton = document.createElement("button");
        editButton.textContent = "Edit";
        editButton.className = "btn btn--primary";
        editButton.onclick = () => {
            window.location.href = `edit_reservation.php?id=${res["id"]}&start_date=${res["start_date"]}&end_date=${res["end_date"]}`;
        };
        editCol.appendChild(editButton);

        let deleteCol = newRow.insertCell();
        deleteCol.className = "data-table__cell";
        let removeButton = document.createElement("button");
        removeButton.textContent = "Remove";
        removeButton.className = "btn btn--primary";
        removeButton.onclick = () => {
            const confirmed = confirm("Are you sure you want to delete this reservation?");
            if (!confirmed) return;
            $.ajax({
                type: "DELETE",
                url: `api/reservations/${res["id"]}`,
                success: () => {
                    const idx = allReservations.findIndex(x => x.id === res["id"]);
                    if (idx !== -1) allReservations.splice(idx, 1);
                    if (currentPage > 0 && currentPage * 4 >= allReservations.length) currentPage--;
                    render();
                },
                error: () => alert("Could not delete the reservation.")
            });
        };
        deleteCol.appendChild(removeButton);
    }

    $(".data-table tbody").replaceWith(newBody);

    $("#previousButton").prop("disabled", currentPage === 0);
    $("#nextButton").prop("disabled", (currentPage + 1) * 4 >= allReservations.length);
};

const loadReservations = () => {
    $.ajax({
        type: "GET",
        url: "api/reservations",
        success: (data) => {
            try {
                allReservations = (typeof data === 'object') ? data : JSON.parse(data);
                currentPage = 0;
                render();
            } catch (e) {
                alert("Error processing server response.");
            }
        },
        error: () => alert("Could not load reservations.")
    });
};

$(document).ready(() => {
    currentUsername = username;
    loadReservations();

    $("#previousButton").click(() => {
        if (currentPage > 0) { currentPage--; render(); }
    });

    $("#nextButton").click(() => {
        if ((currentPage + 1) * 4 < allReservations.length) { currentPage++; render(); }
    });

    $("#returnButton").click(() => {
        window.location.href = "home.php";
    });
});