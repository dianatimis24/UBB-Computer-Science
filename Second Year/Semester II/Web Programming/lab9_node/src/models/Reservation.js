class Reservation {
    constructor({ id, room_id, room_number, hotel_name, user_name, start_date, end_date }) {
        this.id = id;
        this.roomId = room_id;
        this.roomNumber = room_number;
        this.hotelName = hotel_name;
        this.userName = user_name;
        this.startDate = start_date;
        this.endDate = end_date;
    }
}

module.exports = Reservation;