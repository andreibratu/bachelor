using lab8.Models;
using System.Threading.Tasks;

namespace lab8.Services
{
    public interface IAuthenticationService
    {
        string LoginUser(string username, string password);
        Task<string> RegisterUser(string username, string password);
    }
}