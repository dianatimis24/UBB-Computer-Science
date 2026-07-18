$(document).ready(() => {
    $("#insertLogButton").click(() => {
        const name = $("#nameField").val().trim();
        const address = $("#addressField").val().trim();

        if (name.length === 0 || address.length === 0) {
            alert("Please fill in both the name and the address.");
            return;
        }

        $.ajax({
            type: "POST",
            url: "api/hotels",
            contentType: "application/json",
            data: JSON.stringify({ name, address }),
            success: () => {
                $(".form-group__input").val("");
                alert("Hotel added successfully!");
            },
            error: () => alert("Hotel could not be added!")
        });
    });
});