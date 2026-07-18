let currentPage = 0;
let hotels = [];

const insertData = (newBody) => {
    const start = 4 * currentPage;
    const end = start + 3;

    for (let i = start; i <= end && i < hotels.length; i++) {
        const h = hotels[i];
        let newRow = newBody.insertRow();
        newRow.className = "data-table__row";

        for (let key of ["id", "name", "address"]) {
            let cell = newRow.insertCell();
            cell.className = "data-table__cell";
            cell.textContent = h[key];
        }

        let addCell = newRow.insertCell();
        addCell.className = "data-table__cell";
        let addBtn = document.createElement("button");
        addBtn.textContent = "+";
        addBtn.className = "btn btn--primary";
        addBtn.onclick = () => {
            window.location.href = `add_room.php?hotel_id=${h["id"]}`;
        };
        addCell.appendChild(addBtn);

        let editCell = newRow.insertCell();
        editCell.className = "data-table__cell";
        let editBtn = document.createElement("button");
        editBtn.textContent = "Edit";
        editBtn.className = "btn btn--primary";
        editBtn.onclick = () => openEditModal(h);
        editCell.appendChild(editBtn);

        let deleteCell = newRow.insertCell();
        deleteCell.className = "data-table__cell";
        let deleteBtn = document.createElement("button");
        deleteBtn.textContent = "Delete";
        deleteBtn.className = "btn btn--primary";
        deleteBtn.onclick = () => {
            const confirmed = confirm(
                `Delete hotel "${h["name"]}"? All its rooms and reservations will also be deleted.`
            );
            if (!confirmed) return;
            $.ajax({
                type: "DELETE",
                url: `api/hotels/${h["id"]}`,
                success: () => {
                    const idx = hotels.findIndex(x => x.id === h["id"]);
                    if (idx !== -1) hotels.splice(idx, 1);
                    if (currentPage > 0 && currentPage * 4 >= hotels.length) currentPage--;
                    render();
                },
                error: () => alert("Could not delete the hotel.")
            });
        };
        deleteCell.appendChild(deleteBtn);
    }

    $("#previousButton").prop("disabled", currentPage === 0);
    $("#nextButton").prop("disabled", (currentPage + 1) * 4 >= hotels.length);
};

const replaceBody = (newBody) => {
    $(".data-table tbody").replaceWith(newBody);
};

const render = () => {
    let nb = document.createElement("tbody");
    insertData(nb);
    replaceBody(nb);
};

const fetchHotels = (url) => {
    currentPage = 0;
    $.ajax({
        type: "GET",
        url: url,
        success: (data) => {
            try {
                hotels = (typeof data === 'object') ? data : JSON.parse(data);
                render();
            } catch (e) {
                alert("Error processing data from server.");
            }
        },
        error: () => alert("Could not load hotels.")
    });
};

const openEditModal = (h) => {
    $("#editHotelId").val(h["id"]);
    $("#editHotelName").val(h["name"]);
    $("#editHotelAddress").val(h["address"]);
    $("#editHotelModal").css("display", "flex");
};

const closeEditModal = () => {
    $("#editHotelModal").css("display", "none");
};

$(document).ready(() => {
    fetchHotels("api/hotels");

    $("#showAllButton").click(() => {
        fetchHotels("api/hotels");
    });

    $("#filterByNameButton").click(() => {
        const val = $("#nameInputFilter").val().trim();
        if (val === "") { alert("Please enter a hotel name."); return; }
        fetchHotels(`api/hotels?name=${encodeURIComponent(val)}`);
    });

    $("#filterByAddressButton").click(() => {
        const val = $("#addressInputFilter").val().trim();
        if (val === "") { alert("Please enter an address."); return; }
        fetchHotels(`api/hotels?address=${encodeURIComponent(val)}`);
    });

    $("#previousButton").click(() => {
        if (currentPage > 0) { currentPage--; render(); }
    });

    $("#nextButton").click(() => {
        if ((currentPage + 1) * 4 < hotels.length) { currentPage++; render(); }
    });

    $("#cancelHotelButton").click(() => closeEditModal());

    $("#saveHotelButton").click(() => {
        const id = parseInt($("#editHotelId").val(), 10);
        const name = $("#editHotelName").val().trim();
        const address = $("#editHotelAddress").val().trim();

        if (name === '' || address === '') {
            alert("Name and address cannot be empty.");
            return;
        }

        $.ajax({
            type: "PUT",
            url: `api/hotels/${id}`,
            contentType: "application/json",
            data: JSON.stringify({ name, address }),
            success: () => {
                closeEditModal();
                alert("Hotel updated successfully!");
                fetchHotels("api/hotels");
            },
            error: () => alert("Could not update the hotel.")
        });
    });

    $("#editHotelModal").click(function (e) {
        if (e.target === this) closeEditModal();
    });
});