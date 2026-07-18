const express = require('express');
const hotelService = require('../services/hotelService');

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

    const { name, address } = request.query;
    const hotels = await hotelService.getHotels(name, address);
    return response.status(200).json(hotels);
});

router.post('/', async (request, response) => {
    if (!isLoggedIn(request, response)) {
        return;
    }

    const { name, address } = request.body;
    if (!name || !address) {
        return response.status(422).json({ error: 'Name and address are required.' });
    }

    const hotel = await hotelService.insertHotel(name, address);
    return response.status(201).json(hotel);
});

router.put('/:id', async (request, response) => {
    if (!isLoggedIn(request, response)) {
        return;
    }

    const id = parseInt(request.params.id);
    const { name, address } = request.body;
    if (!name || !address) {
        return response.status(422).json({ error: 'Name and address are required.' });
    }

    const hotel = await hotelService.updateHotel(id, name, address);
    if (!hotel) {
        return response.status(404).json({ error: 'Hotel not found.' });
    }
    return response.status(200).json(hotel);
});

router.delete('/:id', async (request, response) => {
    if (!isLoggedIn(request, response)) {
        return;
    }

    const id = parseInt(request.params.id);
    const deleted = await hotelService.removeHotel(id);
    if (!deleted) {
        return response.status(404).json({ error: 'Hotel not found.' });
    }
    return response.status(200).json({ message: 'Hotel deleted.' });
});

module.exports = router; 