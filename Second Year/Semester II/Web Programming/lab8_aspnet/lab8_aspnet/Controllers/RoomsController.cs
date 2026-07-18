using lab8_aspnet.DTOs;
using lab8_aspnet.Services.Interfaces;
using Microsoft.AspNetCore.Mvc;

namespace lab8_aspnet.Controllers
{
    [ApiController]
    [Route("api/[controller]")]
    public class RoomsController : ControllerBase
    {
        private readonly IRoomService _roomService;

        public RoomsController(IRoomService roomService)
        {
            _roomService = roomService;
        }

        private bool IsLoggedIn() => HttpContext.Session.GetString("username") != null;

        [HttpGet]
        public async Task<IActionResult> GetRooms([FromQuery] string? category, [FromQuery] string? type, [FromQuery] decimal? maxPrice, [FromQuery] string? hotelName)
        {
            if (!IsLoggedIn())
            {
                return Unauthorized(new { error = "Not logged in." });
            }

            var rooms = await _roomService.GetRoomsAsync(category, type, maxPrice, hotelName);
            return Ok(rooms);
        }

        [HttpPost]
        public async Task<IActionResult> Insert([FromBody] RoomCreateRequest request)
        {
            if (!IsLoggedIn())
            {
                return Unauthorized(new { error = "Not logged in." });
            }

            if (string.IsNullOrWhiteSpace(request.RoomNumber) || string.IsNullOrWhiteSpace(request.Category) ||
                string.IsNullOrWhiteSpace(request.Type) || request.Price <= 0 || request.HotelId <= 0)
            {
                return UnprocessableEntity(new { error = "Invalid room data." });
            }

            var room = await _roomService.InsertRoomAsync(request);
            return StatusCode(201, room);
        }

        [HttpPut("{id}")]
        public async Task<IActionResult> Update(int id, [FromBody] RoomUpdateRequest request)
        {
            if (!IsLoggedIn())
            {
                return Unauthorized(new { error = "Not logged in." });
            }

            if (string.IsNullOrWhiteSpace(request.RoomNumber) || string.IsNullOrWhiteSpace(request.Category) ||
                string.IsNullOrWhiteSpace(request.Type) || request.Price <= 0)
            {
                return UnprocessableEntity(new { error = "Invalid room data." });
            }

            var room = await _roomService.UpdateRoomAsync(id, request);
            if (room == null)
            {
                return NotFound(new { error = "Room not found." });
            }

            return Ok(room);
        }

        [HttpDelete("{id}")]
        public async Task<IActionResult> Delete(int id)
        {
            if (!IsLoggedIn())
            {
                return Unauthorized(new { error = "Not logged in." });
            }

            var deleted = await _roomService.DeleteRoomAsync(id);
            if (!deleted)
            {
                return NotFound(new { error = "Room not found." });
            }

            return Ok(new { message = "Room deleted." });
        }
    }
}