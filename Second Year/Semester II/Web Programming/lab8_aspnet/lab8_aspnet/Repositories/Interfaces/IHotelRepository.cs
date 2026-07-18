using lab8_aspnet.Models;

namespace lab8_aspnet.Repositories.Interfaces
{
    public interface IHotelRepository
    {
        Task<List<Hotel>> GetHotelsAsync(string? name, string? address);
        Task<Hotel> InsertHotelAsync(Hotel hotel);
        Task<Hotel?> UpdateHotelAsync(int id, string name, string address);
        Task<bool> DeleteHotelAsync(int id);
    }
}