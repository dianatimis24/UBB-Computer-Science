class Room {
    constructor({ id, hotel_id, hotel_name, room_number, category, type, price }) {
        this.id = id;
        this.hotelId = hotel_id;
        this.hotelName = hotel_name;
        this.roomNumber = room_number;
        this.category = category;
        this.type = type;
        this.price = price;
    }
}

module.exports = Room;