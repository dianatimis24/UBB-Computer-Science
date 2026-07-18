const roomRepository = require('../repositories/roomRepository');

function toDto(room) {
    return {
        id: room.id,
        hotel_name: room.hotelName,
        room_number: room.roomNumber,
        category: room.category,
        type: room.type,
        price: room.price
    };
}

async function getRooms(category, type, maxPrice, hotelName) {
    const rooms = await roomRepository.getRooms(category, type, maxPrice, hotelName);
    return rooms.map(toDto);
}

async function insertRoom(hotelId, roomNumber, category, type, price) {
    const idCreatedRoom = await roomRepository.insertRoom(hotelId, roomNumber, category, type, price);
    const createdRoom = await roomRepository.getRoomById(idCreatedRoom);
    return toDto(createdRoom);
}

async function updateRoom(id, roomNumber, category, type, price) {
    const updatedRoom = await roomRepository.updateRoom(id, roomNumber, category, type, price);
    if (!updatedRoom) {
        return null;
    }
    const room = await roomRepository.getRoomById(id);
    return toDto(room);
}

async function removeRoom(id) {
    return await roomRepository.removeRoom(id);
}

module.exports = {
    getRooms,
    insertRoom,
    updateRoom,
    removeRoom
};