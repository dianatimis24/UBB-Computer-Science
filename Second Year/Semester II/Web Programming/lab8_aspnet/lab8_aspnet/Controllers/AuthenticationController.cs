using lab8_aspnet.DTOs;
using lab8_aspnet.Services.Interfaces;
using Microsoft.AspNetCore.Identity.Data;
using Microsoft.AspNetCore.Mvc;

namespace lab8_aspnet.Controllers
{
    [ApiController]
    [Route("api/[controller]")]
    public class AuthenticationController : ControllerBase
    {
        private readonly IAuthenticationService _authService;

        public AuthenticationController(IAuthenticationService authService)
        {
            _authService = authService;
        }

        [HttpPost("login")]
        public async Task<IActionResult> Login([FromBody] LoginRequestDto request)
        {
            if (string.IsNullOrWhiteSpace(request.Username) || string.IsNullOrWhiteSpace(request.Password))
            {
                return BadRequest(new { error = "Username and password are required." });
            }

            var username = await _authService.ValidateUserAsync(request.Username, request.Password);

            if (username == null)
            {
                return Unauthorized(new { error = "Invalid username or password." });
            }

            HttpContext.Session.SetString("username", username);
            return Ok(new { username });
        }

        [HttpPost("logout")]
        public IActionResult Logout()
        {
            HttpContext.Session.Clear();
            return Ok(new { message = "Logged out." });
        }

        [HttpGet("me")]
        public IActionResult Me()
        {
            var username = HttpContext.Session.GetString("username");
            if (username == null)
            {
                return Unauthorized(new { error = "Not logged in." });
            }

            return Ok(new { username });
        }
    }
}