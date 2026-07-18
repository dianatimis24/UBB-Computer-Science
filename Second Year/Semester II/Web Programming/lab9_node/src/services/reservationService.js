const reservationRepository = require('../repositories/reservationRepository');

function toDto(reservation) {
    const formatDate = (value) => {
        if (!value) {
            return '';
        }
        const date = new Date(value);
        return date.toISOString().split('T')[0];
    };

    return {
        id: reservation.id,
        room_number: reservation.roomNumber,
        hotel_name: reservation.hotelName,
        start_date: formatDate(reservation.startDate),
        end_date: formatDate(reservation.endDate)
    };
}

async function getReservationsByUsername(username) {
    const reservations = await reservationRepository.getReservationsByUsername(username);
    return reservations.map(toDto);
}

async function insertReservation(roomId, username, startDate, endDate) {
    const overlap = await reservationRepository.hasOverlap(roomId, startDate, endDate);
    if (overlap) {
        return { overlap: true, reservation: null };
    }

    const idCreatedReservation = await reservationRepository.insertReservation(roomId, username, startDate, endDate);
    const createdReservation = await reservationRepository.getById(idCreatedReservation);
    return { overlap: false, reservation: toDto(createdReservation) };
}

async function updateReservation(id, startDate, endDate) {
    const updated = await reservationRepository.updateReservation(id, startDate, endDate);
    if (!updated) {
        return null;
    }
    const reservation = await reservationRepository.getReservationById(id);
    return toDto(reservation);
}

async function removeReservation(id) {
    return await reservationRepository.removeReservation(id);
}

module.exports = {
    getReservationsByUsername,
    insertReservation,
    updateReservation,
    removeReservation
};