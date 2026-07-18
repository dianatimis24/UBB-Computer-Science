using lab8_aspnet.DTOs;

namespace lab8_aspnet.Services.Interfaces
{
    public interface IReservationService
    {
        Task<List<ReservationDto>> GetReservationsByUsernameAsync(string username);
        Task<(ReservationDto? reservation, bool overlap)> InsertReservationAsync(ReservationCreateRequest request, string username);
        Task<ReservationDto?> UpdateReservationAsync(int id, ReservationUpdateRequest request);
        Task<bool> DeleteReservationAsync(int id);
    }
}