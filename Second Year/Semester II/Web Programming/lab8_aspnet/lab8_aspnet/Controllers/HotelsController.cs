using lab8_aspnet.DTOs;
using lab8_aspnet.Services.Interfaces;
using Microsoft.AspNetCore.Mvc;

namespace lab8_aspnet.Controllers
{
    [ApiController]
    [Route("api/[controller]")]
    public class HotelsController : ControllerBase
    {
        private readonly IHotelService _hotelService;

        public HotelsController(IHotelService hotelService)
        {
            _hotelService = hotelService;
        }

        private bool IsLoggedIn() => HttpContext.Session.GetString("username") != null;

        [HttpGet]
        public async Task<IActionResult> GetHotels([FromQuery] string? name, [FromQuery] string? address)
        {
            if (!IsLoggedIn())
            {
                return Unauthorized(new { error = "Not logged in." });
            }

            var hotels = await _hotelService.GetHotelsAsync(name, address);
            return Ok(hotels);
        }

        [HttpPost]
        public async Task<IActionResult> Insert([FromBody] HotelCreateRequest request)
        {
            if (!IsLoggedIn())
            {
                return Unauthorized(new { error = "Not logged in." });
            }

            if (string.IsNullOrWhiteSpace(request.Name) || string.IsNullOrWhiteSpace(request.Address))
            {
                return UnprocessableEntity(new { error = "Name and address are required." });
            }

            var hotel = await _hotelService.InsertHotelAsync(request);
            return StatusCode(201, hotel);
        }

        [HttpPut("{id}")]
        public async Task<IActionResult> Update(int id, [FromBody] HotelCreateRequest request)
        {
            if (!IsLoggedIn())
            {
                return Unauthorized(new { error = "Not logged in." });
            }

            if (string.IsNullOrWhiteSpace(request.Name) || string.IsNullOrWhiteSpace(request.Address))
            {
                return UnprocessableEntity(new { error = "Name and address are required." });
            }

            var hotel = await _hotelService.UpdateHotelAsync(id, request);
            if (hotel == null)
            {
                return NotFound(new { error = "Hotel not found." });
            }

            return Ok(hotel);
        }

        [HttpDelete("{id}")]
        public async Task<IActionResult> Delete(int id)
        {
            if (!IsLoggedIn())
            {
                return Unauthorized(new { error = "Not logged in." });
            }

            var deleted = await _hotelService.DeleteHotelAsync(id);
            if (!deleted)
            {
                return NotFound(new { error = "Hotel not found." });
            }

            return Ok(new { message = "Hotel deleted." });
        }
    }
}