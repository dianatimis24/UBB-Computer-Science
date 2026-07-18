const express = require('express');
const reservationService = require('../services/reservationService');

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

    const reservations = await reservationService.getReservationsByUsername(request.session.username);
    return response.status(200).json(reservations);
});

router.post('/', async (request, response) => {
    if (!isLoggedIn(request, response)) {
        return;
    }

    const { roomId, startDate, endDate } = request.body;
    if (!roomId || !startDate || !endDate) {
        return response.status(422).json({ error: 'Invalid reservation data.' });
    }
    if (startDate >= endDate) {
        return response.status(422).json({ error: 'Start date must be before end date.' });
    }

    const { overlap, reservation } = await reservationService.insertReservation(
        parseInt(roomId),
        request.session.username,
        startDate,
        endDate
    );

    if (overlap) {
        return response.status(409).json({ error: 'Room is not available for those dates.' });
    }
    return response.status(201).json(reservation);
});

router.put('/:id', async (request, response) => {
    if (!isLoggedIn(request, response)) {
        return;
    }

    const id = parseInt(request.params.id);
    const { startDate, endDate } = request.body;
    if (!startDate || !endDate) {
        return response.status(422).json({ error: 'Invalid dates.' });
    }
    if (startDate >= endDate) {
        return response.status(422).json({ error: 'Start date must be before end date.' });
    }

    const reservation = await reservationService.updateReservation(id, startDate, endDate);
    if (!reservation) {
        return response.status(404).json({ error: 'Reservation not found.' });
    }
    return response.status(200).json(reservation);
});

router.delete('/:id', async (request, response) => {
    if (!isLoggedIn(request, response)) {
        return;
    }

    const id = parseInt(request.params.id);
    const deleted = await reservationService.removeReservation(id);
    if (!deleted) {
        return response.status(404).json({ error: 'Reservation not found.' });
    }
    return response.status(200).json({ message: 'Reservation deleted.' });
});

module.exports = router; 