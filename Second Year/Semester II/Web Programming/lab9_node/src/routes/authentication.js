const express = require('express');
const authenticationService = require('../services/authenticationService');

const router = express.Router();

router.post('/login', async (request, response) => {
    const { username, password } = request.body;
    if (!username || !password) {
        return response.status(400).json({ error: 'Username and password are required.' });
    }

    const validatedUsername = await authenticationService.validateUser(username, password);
    if (!validatedUsername) {
        return response.status(401).json({ error: 'Invalid username or password.' });
    }

    request.session.username = validatedUsername;
    return response.status(200).json({ username: validatedUsername });
});

router.post('/logout', (request, response) => {
    request.session.destroy((error) => {
        if (error) {
            return response.status(500).json({ error: 'Could not log out.' });
        }
        response.clearCookie('connect.sid');
        return response.status(200).json({ message: 'Logged out.' });
    });
});

router.get('/me', (request, response) => {
    if (!request.session.username) {
        return response.status(401).json({ error: 'Not logged in.' });
    }
    return response.status(200).json({ username: request.session.username });
});

module.exports = router; 