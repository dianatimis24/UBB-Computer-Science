using lab8_aspnet.Data;
using lab8_aspnet.Models;
using lab8_aspnet.Repositories.Interfaces;
using Microsoft.EntityFrameworkCore;

namespace lab8_aspnet.Repositories
{
    public class RoomRepository : IRoomRepository
    {
        private readonly BookingAppDbContext _db;

        public RoomRepository(BookingAppDbContext db)
        {
            _db = db;
        }

        public async Task<List<Room>> GetRoomsAsync(string? category, string? type, decimal? maxPrice, string? hotelName)
        {
            var query = _db.Rooms
                .Include(room => room.Hotel)
                .AsQueryable();

            if (!string.IsNullOrWhiteSpace(category))
            {
                query = query.Where(room => room.Category.Contains(category));
            }

            if (!string.IsNullOrWhiteSpace(type))
            {
                query = query.Where(room => room.Type.Contains(type));
            }

            if (maxPrice.HasValue)
            {
                query = query.Where(room => room.Price < maxPrice.Value);
            }

            if (!string.IsNullOrWhiteSpace(hotelName))
            {
                query = query.Where(room => room.Hotel!.Name.Contains(hotelName));
            }

            return await query
                .OrderBy(room => room.Hotel!.Name)
                .ThenBy(room => room.RoomNumber)
                .ToListAsync();
        }

        public async Task<Room> InsertRoomAsync(Room room)
        {
            _db.Rooms.Add(room);
            await _db.SaveChangesAsync();

            return await _db.Rooms
                .Include(currentRoom => currentRoom.Hotel)
                .FirstAsync(currentRoom => currentRoom.Id == room.Id);
        }

        public async Task<Room?> UpdateRoomAsync(int id, string roomNumber, string category, string type, decimal price)
        {
            var room = await _db.Rooms
                .Include(currentRoom => currentRoom.Hotel)
                .FirstOrDefaultAsync(currentRoom => currentRoom.Id == id);

            if (room == null)
            {
                return null;
            }

            room.RoomNumber = roomNumber;
            room.Category = category;
            room.Type = type;
            room.Price = price;
            await _db.SaveChangesAsync();
            return room;
        }

        public async Task<bool> DeleteRoomAsync(int id)
        {
            var room = await _db.Rooms.FindAsync(id);
            if (room == null)
            {
                return false;
            }

            _db.Rooms.Remove(room);
            await _db.SaveChangesAsync();
            return true;
        }
    }
}