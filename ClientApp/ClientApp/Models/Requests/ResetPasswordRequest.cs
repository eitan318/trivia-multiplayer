using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Requests
{
    class ResetPasswordRequest : IRequest
    {
        public ResetPasswordRequest(string newPassword, string username) {
            this.NewPassword = newPassword;
            this.Username = username;
        }
        public RequestsCodes GetCode() => RequestsCodes.ResetPasswordRequest;
        public string Username { get; set; }
        public string NewPassword {  get; set; }
    }
}
