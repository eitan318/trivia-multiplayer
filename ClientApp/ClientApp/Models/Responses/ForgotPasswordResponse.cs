using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Responses
{
    class ForgotPasswordResponse : Response
    {
        [JsonConstructor]
        private ForgotPasswordResponse(uint status, string emailCode, string username) : base(status)
        {
            this.EmailCode = emailCode;
            this.Username = username;

        }
        public string EmailCode { get; }
        public string Username { get; }
    }
}
