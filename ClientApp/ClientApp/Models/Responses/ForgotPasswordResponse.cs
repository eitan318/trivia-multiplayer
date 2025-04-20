using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Responses
{
    class ForgotPasswordResponse
    {
        //public ForgotPasswordResponse(int status, string emailCode, string username) {
        //    this.Status = status;
        //    this.EmailCode = emailCode;
        //    this.Username = username;

        //}
        public int Status { get; set; }
        public string EmailCode { get; set; }
        public string Username { get; set; }
    }
}
