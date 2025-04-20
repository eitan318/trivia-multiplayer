using System;
using System.CodeDom;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Requests
{
    public struct LoginRequest : IRequest
    {
        public LoginRequest(string username, string password) {
            this.Username = username;
            this.Password = password;
        }
        public RequestsCodes GetCode() => RequestsCodes.LoginRequest;
        public string Username { get; set; }
        public string Password { get; set; }
    }
}
