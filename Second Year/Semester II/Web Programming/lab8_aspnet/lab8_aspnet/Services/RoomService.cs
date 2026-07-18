using lab8_aspnet.DTOs;
using lab8_aspnet.Models;
using lab8_aspnet.Repositories.Interfaces;
using lab8_aspnet.Services.Interfaces;

namespace lab8_aspnet.Services
{
    public class RoomService : IRoomService
    {
        private readonly IRoomRepository _roomRepository;

        public RoomService(IRoomRepository roomRepository)
        {
            _roomRepository = roomRepository;
        }

        private static RoomDto ToDto(Room room) => new RoomDto
        {
            Id = room.Id,
            HotelName = room.Hotel!.Name,
            RoomNumber = room.RoomNumber,
            Category = room.Category,
            Type = room.Type,
            Price = room.Price
        };

        public async Task<List<RoomDto>> GetRoomsAsync(
            string? category, string? type, decimal? maxPrice, string? hotelName) =>
            (await _roomRepository.GetRoomsAsync(category, type, maxPrice, hotelName)).Select(ToDto).ToList();

        public async Task<RoomDto> InsertRoomAsync(RoomCreateRequest request)
        {
            var room = new Room
            {
                HotelId = request.HotelId,
                RoomNumber = request.RoomNumber,
                Category = request.Category,
                Type = request.Type,
                Price = request.Price
            };

            var createdRoom = await _roomRepository.InsertRoomAsync(room);
            return ToDto(createdRoom);
        }

        public async Task<RoomDto?> UpdateRoomAsync(int id, RoomUpdateRequest request)
        {
            var updatedRoom = await _roomRepository.UpdateRoomAsync(id, request.RoomNumber, request.Category, request.Type, request.Price);
            return updatedRoom == null ? null : ToDto(updatedRoom);
        }

        public async Task<bool> DeleteRoomAsync(int id) =>
            await _roomRepository.DeleteRoomAsync(id);
    }
}