using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Requests
{
    /// <summary>
    /// Represents a request for forgot password attempt
    /// </summary>
    class ForgotPasswordRequest : IRequest
    {
        /// <summary>
        /// creates a request for forgot password attempt
        /// </summary>
        /// <param name="email"></param>
        public ForgotPasswordRequest(string email) {
            this.Email = email;
        }
        public RequestsCodes GetCode() => RequestsCodes.SendPasswordResetCodeRequest;
        public string Email { get; }
    }
}
