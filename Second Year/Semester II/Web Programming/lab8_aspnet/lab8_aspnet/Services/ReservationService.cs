using lab8_aspnet.DTOs;
using lab8_aspnet.Models;
using lab8_aspnet.Repositories.Interfaces;
using lab8_aspnet.Services.Interfaces;

namespace lab8_aspnet.Services
{
    public class ReservationService : IReservationService
    {
        private readonly IReservationRepository _reservationRepository;

        public ReservationService(IReservationRepository reservationRepository)
        {
            _reservationRepository = reservationRepository;
        }

        private static ReservationDto ToDto(Reservation reservation) => new ReservationDto
        {
            Id = reservation.Id,
            RoomNumber = reservation.Room!.RoomNumber,
            HotelName = reservation.Room.Hotel!.Name,
            StartDate = reservation.StartDate.ToString("yyyy-MM-dd"),
            EndDate = reservation.EndDate.ToString("yyyy-MM-dd")
        };

        public async Task<List<ReservationDto>> GetReservationsByUsernameAsync(string username) =>
            (await _reservationRepository.GetReservationsByUsernameAsync(username)).Select(ToDto).ToList();

        public async Task<(ReservationDto? reservation, bool overlap)> InsertReservationAsync(ReservationCreateRequest request, string username)
        {
            var overlap = await _reservationRepository.HasOverlapAsync(request.RoomId, request.StartDate, request.EndDate);

            if (overlap)
            {
                return (null, true);
            }

            var reservation = new Reservation
            {
                RoomId = request.RoomId,
                UserName = username,
                StartDate = request.StartDate,
                EndDate = request.EndDate
            };

            var createdReservation = await _reservationRepository.InsertReservationAsync(reservation);
            return (ToDto(createdReservation), false);
        }

        public async Task<ReservationDto?> UpdateReservationAsync(int id, ReservationUpdateRequest request)
        {
            var updatedReservation = await _reservationRepository.UpdateReservationAsync(id, request.StartDate, request.EndDate);
            return updatedReservation == null ? null : ToDto(updatedReservation);
        }

        public async Task<bool> DeleteReservationAsync(int id) =>
            await _reservationRepository.DeleteReservationAsync(id);
    }
}