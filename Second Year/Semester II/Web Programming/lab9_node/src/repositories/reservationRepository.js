const pool = require('../config/db');
const Reservation = require('../models/Reservation');

async function getReservationsByUsername(username) {
    const [rows] = await pool.execute(
        `SELECT reservations.id, reservations.room_id, rooms.room_number, hotels.name AS hotel_name, 
        reservations.user_name, reservations.start_date, reservations.end_date 
        FROM reservations
        JOIN rooms ON reservations.room_id = rooms.id
        JOIN hotels ON rooms.hotel_id = hotels.id 
        WHERE reservations.user_name = ? 
        ORDER BY reservations.start_date DESC`,
        [username]
    );
    return rows.map(row => new Reservation(row));
}

async function getReservationById(id) {
    const [rows] = await pool.execute(
        `SELECT reservations.id, reservations.room_id, rooms.room_number, hotels.name AS hotel_name, 
        reservations.user_name, reservations.start_date, reservations.end_date 
        FROM reservations
        JOIN rooms ON reservations.room_id = rooms.id
        JOIN hotels ON rooms.hotel_id = hotels.id 
        WHERE reservations.id = ?`,
        [id]
    );
    return rows[0] ? new Reservation(rows[0]) : null;
}

async function hasOverlap(roomId, startDate, endDate) {
    const [rows] = await pool.execute(
        `SELECT COUNT(*) AS count FROM reservations
         WHERE room_id = ? AND start_date < ? AND end_date > ?`,
        [roomId, endDate, startDate]
    );
    return rows[0].count > 0;
}

async function insertReservation(roomId, username, startDate, endDate) {
    const [result] = await pool.execute(
        'INSERT INTO reservations (room_id, user_name, start_date, end_date) VALUES (?, ?, ?, ?)',
        [roomId, username, startDate, endDate]
    );
    return result.insertId;
}

async function updateReservation(id, startDate, endDate) {
    const [result] = await pool.execute(
        'UPDATE reservations SET start_date = ?, end_date = ? WHERE id = ?',
        [startDate, endDate, id]
    );
    return result.affectedRows > 0;
}

async function removeReservation(id) {
    const [result] = await pool.execute(
        'DELETE FROM reservations WHERE id = ?',
        [id]
    );
    return result.affectedRows > 0;
}

module.exports = {
    getReservationsByUsername,
    getReservationById,
    hasOverlap,
    insertReservation,
    updateReservation,
    removeReservation
};