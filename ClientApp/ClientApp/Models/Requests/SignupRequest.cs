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
    class SignupRequest : IRequest
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
        public string Username { get;}
        public string Password { get;}
        public string Email { get; }
        public string PhoneNumber { get; }
        public string HouseAddress { get; }
        public string BirthDate { get; }
    }
}
