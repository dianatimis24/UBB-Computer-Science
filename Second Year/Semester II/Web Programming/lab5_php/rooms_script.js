let currentPage = 0;
let rooms = [];

const insertData = (newBody) => {
    const start = 4 * currentPage;
    const end = start + 3;

    for (let i = start; i <= end && i < rooms.length; i++) {
        const r = rooms[i];
        let newRow = newBody.insertRow();
        newRow.className = "data-table__row";

        let checkCell = newRow.insertCell();
        checkCell.className = "data-table__cell";
        let checkbox = document.createElement("input");
        checkbox.type = "checkbox";
        checkbox.className = "room-checkbox";
        checkbox.dataset.roomId = r["id"];
        checkCell.appendChild(checkbox);

        for (let key of ["hotel_name", "room_number", "category", "type", "price"]) {
            let cell = newRow.insertCell();
            cell.className = "data-table__cell";
            cell.textContent = r[key];
        }

        if (userIsLoggedIn) {
            let editCell = newRow.insertCell();
            editCell.className = "data-table__cell";
            let editBtn = document.createElement("button");
            editBtn.textContent = "Edit";
            editBtn.className = "btn btn--primary";
            editBtn.onclick = () => openEditModal(r);
            editCell.appendChild(editBtn);

            let delCell = newRow.insertCell();
            delCell.className = "data-table__cell";
            let delBtn = document.createElement("button");
            delBtn.textContent = "Delete";
            delBtn.className = "btn btn--primary";
            delBtn.onclick = () => {
                const confirmed = confirm(
                    `Delete room ${r["room_number"]} at ${r["hotel_name"]}? This action cannot be undone.`
                );
                if (!confirmed) return;
                $.ajax({
                    type: "DELETE",
                    url: `api/rooms/${r["id"]}`,
                    success: () => {
                        const idx = rooms.findIndex(x => x.id === r["id"]);
                        if (idx !== -1) rooms.splice(idx, 1);
                        if (currentPage > 0 && currentPage * 4 >= rooms.length) currentPage--;
                        render();
                    },
                    error: () => alert("Could not delete the room.")
                });
            };
            delCell.appendChild(delBtn);
        }
    }

    $("#previousButton").prop("disabled", currentPage === 0);
    $("#nextButton").prop("disabled", (currentPage + 1) * 4 >= rooms.length);
};

const replaceBody = (newBody) => {
    $(".data-table tbody").eq(0).replaceWith(newBody);
};

const render = () => {
    let nb = document.createElement("tbody");
    insertData(nb);
    replaceBody(nb);
};

const fetchRooms = (url) => {
    currentPage = 0;
    $.ajax({
        type: "GET",
        url: url,
        success: (data) => {
            try {
                rooms = (typeof data === 'object') ? data : JSON.parse(data);
                render();
            } catch (e) {
                alert("Error loading room data.");
            }
        },
        error: () => alert("Could not load rooms.")
    });
};

const openEditModal = (r) => {
    $("#editRoomId").val(r["id"]);
    $("#editRoomNumber").val(r["room_number"]);
    $("#editCategory").val(r["category"]);
    $("#editType").val(r["type"]);
    $("#editPrice").val(r["price"]);
    $("#editRoomModal").css("display", "flex");
};

const closeEditModal = () => {
    $("#editRoomModal").css("display", "none");
};

const bookRooms = (roomIds, startDate, endDate, successCount, overlapCount, index, done) => {
    if (index >= roomIds.length) {
        done(successCount, overlapCount);
        return;
    }
    $.ajax({
        type: "POST",
        url: "api/reservations",
        contentType: "application/json",
        data: JSON.stringify({
            roomId: roomIds[index],
            startDate: startDate,
            endDate: endDate
        }),
        success: () => {
            bookRooms(roomIds, startDate, endDate, successCount + 1, overlapCount, index + 1, done);
        },
        error: (xhr) => {
            const newOverlap = xhr.status === 409 ? overlapCount + 1 : overlapCount;
            bookRooms(roomIds, startDate, endDate, successCount, newOverlap, index + 1, done);
        }
    });
};

$(document).ready(() => {
    fetchRooms("api/rooms");

    $("#showAllButton").click(() => {
        fetchRooms("api/rooms");
    });

    $("#filterByCategoryButton").click(() => {
        const val = $("#categoryInputFilter").val().trim();
        if (val === "") { alert("Please enter a category."); return; }
        fetchRooms(`api/rooms?category=${encodeURIComponent(val)}`);
    });

    $("#filterByTypeButton").click(() => {
        const val = $("#typeInputFilter").val().trim();
        if (val === "") { alert("Please enter a type."); return; }
        fetchRooms(`api/rooms?type=${encodeURIComponent(val)}`);
    });

    $("#filterByPriceButton").click(() => {
        const val = parseFloat($("#priceInputFilter").val().trim());
        if (isNaN(val) || val <= 0) { alert("Please enter a valid positive price."); return; }
        fetchRooms(`api/rooms?maxPrice=${val}`);
    });

    $("#filterByHotelButton").click(() => {
        const val = $("#hotelInputFilter").val().trim();
        if (val === "") { alert("Please enter a hotel name."); return; }
        fetchRooms(`api/rooms?hotelName=${encodeURIComponent(val)}`);
    });

    $("#previousButton").click(() => {
        if (currentPage > 0) { currentPage--; render(); }
    });

    $("#nextButton").click(() => {
        if ((currentPage + 1) * 4 < rooms.length) { currentPage++; render(); }
    });

    $("#cancelEditButton").click(() => closeEditModal());

    $("#saveRoomButton").click(() => {
        const id = parseInt($("#editRoomId").val(), 10);
        const room_number = $("#editRoomNumber").val().trim();
        const category = $("#editCategory").val().trim();
        const type = $("#editType").val().trim();
        const price = parseFloat($("#editPrice").val().trim());

        if (!room_number || !category || !type) {
            alert("Room number, category, and type cannot be empty.");
            return;
        }
        if (isNaN(price) || price <= 0) {
            alert("Please enter a valid price.");
            return;
        }

        $.ajax({
            type: "PUT",
            url: `api/rooms/${id}`,
            contentType: "application/json",
            data: JSON.stringify({ roomNumber: room_number, category, type, price }),
            success: () => {
                closeEditModal();
                alert("Room updated successfully!");
                fetchRooms("api/rooms");
            },
            error: () => alert("Could not update the room.")
        });
    });

    $("#editRoomModal").click(function (e) {
        if (e.target === this) closeEditModal();
    });

    $("#bookSelectedButton").click(() => {
        if (!userIsLoggedIn) {
            alert("Please log in to make a reservation.");
            window.location.href = "login.php";
            return;
        }

        const checkedBoxes = $(".room-checkbox:checked");
        if (checkedBoxes.length === 0) {
            alert("Please select at least one room.");
            return;
        }

        const startDate = $("#bookStartDate").val();
        const endDate = $("#bookEndDate").val();

        if (!startDate || !endDate) {
            alert("Please fill in both the start and end dates.");
            return;
        }
        if (startDate >= endDate) {
            alert("Start date must be before end date.");
            return;
        }

        const roomIds = checkedBoxes.map(function () {
            return parseInt($(this).data("room-id"), 10);
        }).get();

        const resultEl = $("#bookingResult");
        resultEl.text("Processing booking…").css("color", "#333");

        bookRooms(roomIds, startDate, endDate, 0, 0, 0, (successCount, overlapCount) => {
            const total = roomIds.length;
            if (successCount === total) {
                resultEl.text(`✓ All ${total} room(s) booked successfully!`).css("color", "#468847");
            } else if (overlapCount === total) {
                resultEl.text("✕ None of the selected rooms are available for those dates.").css("color", "#d9534f");
            } else if (successCount === 0) {
                resultEl.text("✕ No rooms could be booked. Please try again.").css("color", "#d9534f");
            } else {
                let msg = `⚠ ${successCount} of ${total} room(s) booked.`;
                if (overlapCount > 0) msg += ` ${overlapCount} room(s) already reserved for those dates.`;
                resultEl.text(msg).css("color", "#e67e22");
            }
            $(".room-checkbox").prop("checked", false);
        });
    });
});