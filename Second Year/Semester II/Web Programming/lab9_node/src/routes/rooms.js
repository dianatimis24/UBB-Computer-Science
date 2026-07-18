const express = require('express');
const roomService = require('../services/roomService');

const router = express.Router();

function isLoggedIn(request, response) {
    if (!request.session.username) {
        response.status(401).json({ error: 'Not logged in.' });
        return false;
    }
    return true;
}

router.get('/', async (request, response) => {
    if (!isLoggedIn(request, response)) {
        return;
    }

    const { category, type, maxPriceString, hotelName } = request.query;
    const maxPrice = maxPriceString ? parseFloat(maxPriceString) : null;

    const rooms = await roomService.getRooms(category, type, maxPrice, hotelName);
    return response.status(200).json(rooms);
});

router.post('/', async (request, response) => {
    if (!isLoggedIn(request, response)) {
        return;
    }

    const { hotelId, roomNumber, category, type, price } = request.body;
    if (!hotelId || !roomNumber || !category || !type || !price) {
        return response.status(422).json({ error: 'Invalid room data.' });
    }

    const room = await roomService.insertHotel(
        parseInt(hotelId),
        roomNumber,
        category,
        type,
        parseFloat(price)
    );
    return response.status(201).json(room);
});

router.put('/:id', async (request, response) => {
    if (!isLoggedIn(request, response)) {
        return;
    }

    const id = parseInt(request.params.id);
    const { roomNumber, category, type, price } = request.body;
    if (!roomNumber || !category || !type || !price) {
        return response.status(422).json({ error: 'Invalid room data.' });
    }

    const room = await roomService.updateRoom(id, roomNumber, category, type, parseFloat(price));
    if (!room) {
        return response.status(404).json({ error: 'Room not found.' });
    }
    return response.status(200).json(room);
});

router.delete('/:id', async (request, response) => {
    if (!isLoggedIn(request, response)) {
        return;
    }

    const id = parseInt(request.params.id);
    const deleted = await roomService.removeRoom(id);
    if (!deleted) {
        return response.status(404).json({ error: 'Room not found.' });
    }
    return response.status(200).json({ message: 'Room deleted.' });
});

module.exports = router; 