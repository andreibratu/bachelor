using lab8.DTOs;
using lab8.Services;
using Microsoft.AspNetCore.Mvc;

namespace lab8.Controllers
{
    [Route("api/login")]
    [ApiController]
    public class LoginController : ControllerBase
    {
        private readonly IAuthenticationService authenticationService;

        public LoginController(IAuthenticationService authenticationService)
        {
            this.authenticationService = authenticationService;
        }

        [HttpPost]
        public ActionResult<string> Login(UserInputDTO credentials)
        {
            string token = authenticationService.LoginUser(credentials.Username, credentials.Password);

            if (token == null)
            {
                return BadRequest("Invalid credentials");
            }

            return Ok(token);
        }
    }
}