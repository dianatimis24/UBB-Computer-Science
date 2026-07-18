using lab8_aspnet.DTOs;
using lab8_aspnet.Services.Interfaces;
using Microsoft.AspNetCore.Mvc;

namespace lab8_aspnet.Controllers
{
    [ApiController]
    [Route("api/[controller]")]
    public class ReservationsController : ControllerBase
    {
        private readonly IReservationService _reservationService;

        public ReservationsController(IReservationService reservationService)
        {
            _reservationService = reservationService;
        }

        private bool IsLoggedIn() => HttpContext.Session.GetString("username") != null;

        private string GetUsername() => HttpContext.Session.GetString("username")!;

        [HttpGet]
        public async Task<IActionResult> GetByUsername()
        {
            if (!IsLoggedIn())
            {
                return Unauthorized(new { error = "Not logged in." });
            }

            var reservations = await _reservationService.GetReservationsByUsernameAsync(GetUsername());
            return Ok(reservations);
        }

        [HttpPost]
        public async Task<IActionResult> Insert([FromBody] ReservationCreateRequest request)
        {
            if (!IsLoggedIn())
            {
                return Unauthorized(new { error = "Not logged in." });
            }

            if (request.RoomId <= 0 || request.StartDate == default || request.EndDate == default)
            {
                return UnprocessableEntity(new { error = "Invalid reservation data." });
            }

            if (request.StartDate >= request.EndDate)
            {
                return UnprocessableEntity(new { error = "Start date must be before end date." });
            }

            var (reservation, overlap) = await _reservationService.InsertReservationAsync(request, GetUsername());

            if (overlap)
            {
                return Conflict(new { error = "Room is not available for those dates." });
            }

            return StatusCode(201, reservation);
        }

        [HttpPut("{id}")]
        public async Task<IActionResult> Update(int id, [FromBody] ReservationUpdateRequest request)
        {
            if (!IsLoggedIn())
            {
                return Unauthorized(new { error = "Not logged in." });
            }

            if (request.StartDate == default || request.EndDate == default)
            {
                return UnprocessableEntity(new { error = "Invalid dates." });
            }

            if (request.StartDate >= request.EndDate)
            {
                return UnprocessableEntity(new { error = "Start date must be before end date." });
            }

            var reservation = await _reservationService.UpdateReservationAsync(id, request);
            if (reservation == null)
            {
                return NotFound(new { error = "Reservation not found." });
            }

            return Ok(reservation);
        }

        [HttpDelete("{id}")]
        public async Task<IActionResult> Delete(int id)
        {
            if (!IsLoggedIn())
            {
                return Unauthorized(new { error = "Not logged in." });
            }

            var deleted = await _reservationService.DeleteReservationAsync(id);
            if (!deleted)
            {
                return NotFound(new { error = "Reservation not found." });
            }

            return Ok(new { message = "Reservation deleted." });
        }
    }
}