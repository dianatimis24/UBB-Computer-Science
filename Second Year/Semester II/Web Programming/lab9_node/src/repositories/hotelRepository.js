const pool = require('../config/db');
const Hotel = require('../models/Hotel');

async function getHotels(name, address) {
    let query = 'SELECT * FROM hotels';
    const parameters = [];

    if (name) {
        query += ' AND name LIKE ?';
        parameters.push(`%${name}%`);
    }

    if (address) {
        query += ' AND address LIKE ?';
        parameters.push(`%${address}%`);
    }

    query += ' ORDER BY id';

    const [rows] = await pool.execute(query, parameters);
    return rows.map(row => new Hotel(row));
}

async function getHotelById(id) {
    const [rows] = await pool.execute(
        'SELECT * FROM hotels WHERE id = ?',
        [id]
    );
    return rows[0] ? new Hotel(rows[0]) : null;
}

async function insertHotel(name, address) {
    const [result] = await pool.execute(
        'INSERT INTO hotels (name, address) VALUES (?, ?)',
        [name, address]
    );
    return result.insertId;
}

async function updateHotel(id, name, address) {
    const [result] = await pool.execute(
        'UPDATE hotels SET name = ?, address = ? WHERE id = ?',
        [name, address, id]
    );
    return result.affectedRows > 0;
}

async function removeHotel(id) {
    const [result] = await pool.execute(
        'DELETE FROM hotels WHERE id = ?',
        [id]
    );
    return result.affectedRows > 0;
}

module.exports = {
    getHotels,
    getHotelById,
    insertHotel,
    updateHotel,
    removeHotel
};