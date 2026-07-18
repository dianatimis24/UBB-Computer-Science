using lab8_aspnet.Models;

namespace lab8_aspnet.Repositories.Interfaces
{
    public interface IReservationRepository
    {
        Task<List<Reservation>> GetReservationsByUsernameAsync(string username);
        Task<bool> HasOverlapAsync(int roomId, DateOnly startDate, DateOnly endDate);
        Task<Reservation> InsertReservationAsync(Reservation reservation);
        Task<Reservation?> UpdateReservationAsync(int id, DateOnly startDate, DateOnly endDate);
        Task<bool> DeleteReservationAsync(int id);
    }
}