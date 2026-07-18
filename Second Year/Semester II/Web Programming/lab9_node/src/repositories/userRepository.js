const pool = require('../config/db');
const User = require('../models/User');

async function getUserByUsername(username) {
    const [rows] = await pool.execute(
        'SELECT * FROM users WHERE username = ?',
        [username]
    );
    return rows[0] ? new User(rows[0]) : null;
}

module.exports = {
    getUserByUsername
};