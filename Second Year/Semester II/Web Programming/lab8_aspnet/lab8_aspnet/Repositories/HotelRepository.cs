using lab8_aspnet.Data;
using lab8_aspnet.Models;
using lab8_aspnet.Repositories.Interfaces;
using Microsoft.EntityFrameworkCore;

namespace lab8_aspnet.Repositories
{
    public class HotelRepository : IHotelRepository
    {
        private readonly BookingAppDbContext _db;

        public HotelRepository(BookingAppDbContext db)
        {
            _db = db;
        }

        public async Task<List<Hotel>> GetHotelsAsync(string? name, string? address)
        {
            var query = _db.Hotels.AsQueryable();

            if (!string.IsNullOrWhiteSpace(name))
            {
                query = query.Where(hotel => hotel.Name.Contains(name));
            }

            if (!string.IsNullOrWhiteSpace(address))
            {
                query = query.Where(hotel => hotel.Address.Contains(address));
            }

            return await query.OrderBy(hotel => hotel.Id).ToListAsync();
        }

        public async Task<Hotel> InsertHotelAsync(Hotel hotel)
        {
            _db.Hotels.Add(hotel);
            await _db.SaveChangesAsync();
            return hotel;
        }

        public async Task<Hotel?> UpdateHotelAsync(int id, string name, string address)
        {
            var hotel = await _db.Hotels.FindAsync(id);
            if (hotel == null)
            { 
                return null; 
            }

            hotel.Name = name;
            hotel.Address = address;
            await _db.SaveChangesAsync();
            return hotel;
        }

        public async Task<bool> DeleteHotelAsync(int id)
        {
            var hotel = await _db.Hotels.FindAsync(id);
            if (hotel == null)
            {
                return false;
            }

            _db.Hotels.Remove(hotel);
            await _db.SaveChangesAsync();
            return true;
        }
    }
}