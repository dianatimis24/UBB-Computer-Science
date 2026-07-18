using lab8_aspnet.Repositories.Interfaces;
using lab8_aspnet.Services.Interfaces;

namespace lab8_aspnet.Services
{
    public class AuthenticationService : IAuthenticationService
    {
        private readonly IUserRepository _userRepository;

        public AuthenticationService(IUserRepository userRepository)
        {
            _userRepository = userRepository;
        }

        public async Task<string?> ValidateUserAsync(string username, string password)
        {
            var user = await _userRepository.GetUserByUsernameAsync(username);

            if (user == null || user.Password != password)
            {
                return null;
            }

            return user.Username;
        }
    }
}