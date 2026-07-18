using lab8_aspnet.DTOs;
using lab8_aspnet.Models;
using lab8_aspnet.Repositories.Interfaces;
using lab8_aspnet.Services.Interfaces;

namespace lab8_aspnet.Services
{
    public class HotelService : IHotelService
    {
        private readonly IHotelRepository _hotelRepository;

        public HotelService(IHotelRepository hotelRepository)
        {
            _hotelRepository = hotelRepository;
        }

        private static HotelDto ToDto(Hotel hotel) => new HotelDto
        {
            Id = hotel.Id,
            Name = hotel.Name,
            Address = hotel.Address
        };

        public async Task<List<HotelDto>> GetHotelsAsync(string? name, string? address) =>
            (await _hotelRepository.GetHotelsAsync(name, address)).Select(ToDto).ToList();

        public async Task<HotelDto> InsertHotelAsync(HotelCreateRequest request)
        {
            var hotel = new Hotel
            {
                Name = request.Name,
                Address = request.Address
            };

            var createdHotel = await _hotelRepository.InsertHotelAsync(hotel);
            return ToDto(createdHotel);
        }

        public async Task<HotelDto?> UpdateHotelAsync(int id, HotelCreateRequest request)
        {
            var updatedHotel = await _hotelRepository.UpdateHotelAsync(id, request.Name, request.Address);
            return updatedHotel == null ? null : ToDto(updatedHotel);
        }

        public async Task<bool> DeleteHotelAsync(int id) =>
            await _hotelRepository.DeleteHotelAsync(id);
    }
}