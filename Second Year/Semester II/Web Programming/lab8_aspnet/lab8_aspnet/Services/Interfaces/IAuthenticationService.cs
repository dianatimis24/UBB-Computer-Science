namespace lab8_aspnet.Services.Interfaces
{
    public interface IAuthenticationService
    {
        Task<string?> ValidateUserAsync(string username, string password);
    }
}