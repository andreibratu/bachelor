using lab8.Models;

namespace lab8.DTOs
{
    public class UserOutputDTO
    {
        public long Id { get; set; }

        public string Username { get; set; }

        public UserOutputDTO(User user)
        {
            Id = user.Id;
            Username = user.Username;
        }
    }
}
