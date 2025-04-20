using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Requests
{
    class ForgotPasswordRequest : IRequest
    {
        public ForgotPasswordRequest(string email) {
            this.Email = email;
        }
        public RequestsCodes GetCode() => RequestsCodes.ForgotPasswordRequest;
        public string Email { get; set; }
    }
}
