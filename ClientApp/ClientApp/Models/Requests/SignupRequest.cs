using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Requests
{
    /// <summary>
    /// Represents a request for signing up
    /// /// </summary>
    public struct SignupRequest : IRequest
    {
        public SignupRequest(string username, string password, 
            string email, string phoneNumber, string housAddress, string birthDate) {
            this.Username = username;
            this.Password = password;
            this.Email = email;
            this.PhoneNumber = phoneNumber;
            this.BirthDate = birthDate;
            this.HouseAddress = housAddress;
        }
        public RequestsCodes GetCode() => RequestsCodes.SignupRequest;
        public string Username { get; set; }
        public string Password { get; set; }
        public string Email { get; set; }
        public string PhoneNumber { get; set; }
        public string HouseAddress { get; set; }
        public string BirthDate { get; set; }
    }
}
