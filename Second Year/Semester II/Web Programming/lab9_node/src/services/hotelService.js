const hotelRepository = require('../repositories/hotelRepository');

function toDto(hotel) {
    return {
        id: hotel.id,
        name: hotel.name,
        address: hotel.address
    };
}

async function getHotels(name, address) {
    const hotels = await hotelRepository.getHotels(name, address);
    return hotels.map(toDto);
}

async function insertHotel(name, address) {
    const idCreatedHotel = await hotelRepository.insertHotel(name, address);
    const createdHotel = await hotelRepository.getHotelById(idCreatedHotel);
    return toDto(createdHotel);
}

async function updateHotel(id, name, address) {
    const updatedHotel = await hotelRepository.updateHotel(id, name, address);
    if (!updatedHotel) {
        return null;
    }
    const hotel = await hotelRepository.getHotelById(id);
    return toDto(hotel);
}

async function removeHotel(id) {
    return await hotelRepository.removeHotel(id);
}

module.exports = {
    getHotels,
    insertHotel,
    updateHotel,
    removeHotel
};