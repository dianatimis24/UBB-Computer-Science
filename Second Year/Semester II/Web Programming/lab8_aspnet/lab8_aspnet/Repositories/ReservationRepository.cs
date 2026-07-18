using lab8_aspnet.Data;
using lab8_aspnet.Models;
using lab8_aspnet.Repositories.Interfaces;
using Microsoft.EntityFrameworkCore;

namespace lab8_aspnet.Repositories
{
    public class ReservationRepository : IReservationRepository
    {
        private readonly BookingAppDbContext _db;

        public ReservationRepository(BookingAppDbContext db)
        {
            _db = db;
        }

        public async Task<List<Reservation>> GetReservationsByUsernameAsync(string username) =>
            await _db.Reservations
                .Include(reservation => reservation.Room)
                .ThenInclude(reservation => reservation!.Hotel)
                .Where(reservation => reservation.UserName == username)
                .OrderByDescending(reservation => reservation.StartDate)
                .ToListAsync();

        public async Task<bool> HasOverlapAsync(int roomId, DateOnly startDate, DateOnly endDate) =>
            await _db.Reservations.AnyAsync(reservation =>
                reservation.RoomId == roomId &&
                reservation.StartDate < endDate &&
                reservation.EndDate > startDate);

        public async Task<Reservation> InsertReservationAsync(Reservation reservation)
        {
            _db.Reservations.Add(reservation);
            await _db.SaveChangesAsync();

            return await _db.Reservations
                .Include(currentReservation => currentReservation.Room)
                .ThenInclude(currentReservation => currentReservation!.Hotel)
                .FirstAsync(currentReservation => currentReservation.Id == reservation.Id);
        }

        public async Task<Reservation?> UpdateReservationAsync(int id, DateOnly startDate, DateOnly endDate)
        {
            var reservation = await _db.Reservations
                .Include(currentReservation => currentReservation.Room)
                .ThenInclude(currentReservation => currentReservation!.Hotel)
                .FirstOrDefaultAsync(currentReservation => currentReservation.Id == id);

            if (reservation == null)
            {
                return null;
            }

            reservation.StartDate = startDate;
            reservation.EndDate = endDate;
            await _db.SaveChangesAsync();
            return reservation;
        }

        public async Task<bool> DeleteReservationAsync(int id)
        {
            var reservation = await _db.Reservations.FindAsync(id);
            if (reservation == null)
            {
                return false;
            }

            _db.Reservations.Remove(reservation);
            await _db.SaveChangesAsync();
            return true;
        }
    }
}