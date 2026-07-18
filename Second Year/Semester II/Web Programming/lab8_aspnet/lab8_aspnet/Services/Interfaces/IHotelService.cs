using lab8_aspnet.DTOs;

namespace lab8_aspnet.Services.Interfaces
{
    public interface IHotelService
    {
        Task<List<HotelDto>> GetHotelsAsync(string? name, string? address);
        Task<HotelDto> InsertHotelAsync(HotelCreateRequest request);
        Task<HotelDto?> UpdateHotelAsync(int id, HotelCreateRequest request);
        Task<bool> DeleteHotelAsync(int id);
    }
}