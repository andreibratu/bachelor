using System.Collections.Generic;
using System.Security.Principal;

namespace lab8.Models
{
    public class User
    {

        public User() { }

        public User(string username, string password)
        {
            Username = username;
            this.Password = password;
        }

        public long Id { get; set; }
        public string Username { get; set; }
        public string Password { get; set; }

        public virtual List<Document> Documents { get; set; }
    }
}
