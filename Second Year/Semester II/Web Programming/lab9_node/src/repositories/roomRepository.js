const pool = require('../config/db');
const Room = require('../models/Room');

async function getRooms(category, type, maxPrice, hotelName) {
    let query = `
    SELECT rooms.id, rooms.hotel_id, hotels.name AS hotel_name, 
    rooms.room_number, rooms.category, rooms.type, rooms.price
    FROM rooms INNER JOIN hotels ON rooms.hotel_id = hotels.id
    `;
    const parameters = [];

    if (category) {
        query += ' AND rooms.category LIKE ?';
        parameters.push(`%${category}%`);
    }

    if (type) {
        query += ' AND rooms.type LIKE ?';
        parameters.push(`%${type}%`);
    }

    if (maxPrice) {
        query += ' AND rooms.price < ?';
        parameters.push(maxPrice);
    }

    if (hotelName) {
        query += ' AND hotels.name LIKE ?';
        parameters.push(`%${hotelName}%`);
    }

    query += ' ORDER BY hotels.name, rooms.room_number';

    const [rows] = await pool.execute(query, parameters);
    return rows.map(row => new Room(row));
}

async function getRoomById(id) {
    const [rows] = await pool.execute(
        `SELECT rooms.id, rooms.hotel_id, hotels.name AS hotel_name, 
        rooms.room_number, rooms.category, rooms.type, rooms.price
        FROM rooms INNER JOIN hotels ON rooms.hotel_id = hotels.id WHERE rooms.id = ?`,
        [id]
    );
    return rows[0] ? new Room(rows[0]) : null;
}

async function insertRoom(hotelId, roomNumber, category, type, price) {
    const [result] = await pool.execute(
        'INSERT INTO rooms (hotel_id, room_number, category, type, price) VALUES (?, ?, ?, ?, ?)',
        [hotelId, roomNumber, category, type, price]
    );
    return result.insertId;
}

async function updateRoom(id, roomNumber, category, type, price) {
    const [result] = await pool.execute(
        'UPDATE rooms SET room_number = ?, category = ?, type = ?, price = ? WHERE id = ?',
        [roomNumber, category, type, price, id]
    );
    return result.affectedRows > 0;
}

async function removeRoom(id) {
    const [result] = await pool.execute(
        'DELETE FROM rooms WHERE id = ?',
        [id]
    );
    return result.affectedRows > 0;
}

module.exports = {
    getRooms,
    getRoomById,
    insertRoom,
    updateRoom,
    removeRoom
};