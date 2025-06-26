using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models
{
    class UserRecord
    {
        public UserRecord(string username, string password, 
            string email, string phoneNumber, string houseAddress, string birthDate) {
            this.Username = username;
            this.Password = password;
            this.Email = email;
            this.PhoneNumber = phoneNumber;
            this.BirthDate = birthDate;
            this.HouseAddress = houseAddress;
        }
        public string Username { get; }
        public string Password { get; }
        public string Email { get; }
        public string PhoneNumber { get; }
        public string HouseAddress { get; }
        public string BirthDate { get;  }
    }
}
