using lab8_aspnet.Data;
using lab8_aspnet.Models;
using lab8_aspnet.Repositories.Interfaces;
using Microsoft.EntityFrameworkCore;

namespace lab8_aspnet.Repositories
{
    public class UserRepository : IUserRepository
    {
        private readonly BookingAppDbContext _db;

        public UserRepository(BookingAppDbContext db)
        {
            _db = db;
        }

        public async Task<User?> GetUserByUsernameAsync(string username) =>
            await _db.Users.FirstOrDefaultAsync(user => user.Username == username);
    }
}