using System.Threading.Tasks;
using lab8.DTOs;
using lab8.Services;
using Microsoft.AspNetCore.Mvc;

namespace lab8.Controllers
{
    [Route("api/register")]
    [ApiController]
    public class RegisterController : ControllerBase
    {
        private readonly IAuthenticationService authenticationService;

        public RegisterController(IAuthenticationService authenticationService)
        {
            this.authenticationService = authenticationService;
        }

        [HttpPost]
        public async Task<ActionResult<string>> Register(UserInputDTO credentials)
        {
            string token = await authenticationService.RegisterUser(credentials.Username, credentials.Password);

            if (token == null)
            {
                return Conflict("Username taken");
            }

            return Ok(token);
        }
    }
}