using lab8_aspnet.Models;

namespace lab8_aspnet.Repositories.Interfaces
{
    public interface IUserRepository
    {
        Task<User?> GetUserByUsernameAsync(string username);
    }
}