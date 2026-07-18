const userRepository = require('../repositories/userRepository');

async function validateUser(username, password) {
    const user = await userRepository.getUserByUsername(username);

    if (!user || user.password !== password) {
        return null;
    }

    return user.username;
}

module.exports = {
    validateUser
};