$(document).ready(function () {
    let sortState = {};

    $(".table__cell--header").click(function () {
        let columnIndex = $(this).data("col");
        let rows = $(".table__body .table__row").get();

        sortState[columnIndex] = !sortState[columnIndex];

        rows.sort(function (firstRow, secondRow) {
            let firstValue = $(firstRow).children().eq(columnIndex).text();
            let secondValue = $(secondRow).children().eq(columnIndex).text();

            if ($.isNumeric(firstValue) && $.isNumeric(secondValue)) {
                firstValue = Number(firstValue);
                secondValue = Number(secondValue);
            }

            if (firstValue < secondValue) return sortState[columnIndex] ? -1 : 1;
            if (firstValue > secondValue) return sortState[columnIndex] ? 1 : -1;
            return 0;
        });

        $.each(rows, function (index, row) {
            $(".table__body").append(row);
        });
    });

    $(".table__cell--footer").click(function () {
        let currentColumnIndex = $(this).data("col");
        let nextColumnIndex = (currentColumnIndex + 1) % 4;

        $(".table__body .table__row").each(function () {
            let cells = $(this).children();

            let temporary = cells.eq(currentColumnIndex).html();
            cells.eq(currentColumnIndex).html(cells.eq(nextColumnIndex).html());
            cells.eq(nextColumnIndex).html(temporary);
        });

        let headers = $(".table__cell--header");
        let temporaryHeader = headers.eq(currentColumnIndex).text();
        headers.eq(currentColumnIndex).text(headers.eq(nextColumnIndex).text());
        headers.eq(nextColumnIndex).text(temporaryHeader);
    });
});