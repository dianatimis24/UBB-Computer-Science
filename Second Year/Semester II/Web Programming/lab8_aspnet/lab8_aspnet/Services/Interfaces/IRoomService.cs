using lab8_aspnet.DTOs;

namespace lab8_aspnet.Services.Interfaces
{
    public interface IRoomService
    {
        Task<List<RoomDto>> GetRoomsAsync(string? category, string? type, decimal? maxPrice, string? hotelName);
        Task<RoomDto> InsertRoomAsync(RoomCreateRequest request);
        Task<RoomDto?> UpdateRoomAsync(int id, RoomUpdateRequest request);
        Task<bool> DeleteRoomAsync(int id);
    }
}