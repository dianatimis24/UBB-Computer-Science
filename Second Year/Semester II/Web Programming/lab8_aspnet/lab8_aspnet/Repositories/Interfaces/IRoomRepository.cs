using lab8_aspnet.Models;

namespace lab8_aspnet.Repositories.Interfaces
{
    public interface IRoomRepository
    {
        Task<List<Room>> GetRoomsAsync(string? category, string? type, decimal? maxPrice, string? hotelName);
        Task<Room> InsertRoomAsync(Room room);
        Task<Room?> UpdateRoomAsync(int id, string roomNumber, string category, string type, decimal price);
        Task<bool> DeleteRoomAsync(int id);
    }
}