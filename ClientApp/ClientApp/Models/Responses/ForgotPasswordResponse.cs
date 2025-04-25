using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Responses
{
    class ForgotPasswordResponse : Response
    {
        //public ForgotPasswordResponse(int status, string emailCode, string username) {
        //    this.Status = status;
        //    this.EmailCode = emailCode;
        //    this.Username = username;

        //}
        public string EmailCode { get; set; }
        public string Username { get; set; }
    }
}
