using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ClientApp.Models.Errors;

namespace ClientApp.Models.Responses
{
    class PasswordResetCodeResponse : Response
    {
        [JsonConstructor]
        public PasswordResetCodeResponse(uint status, PasswordResetCodeResponseErrors errors, string emailCode, string username) : base(status)
        {
            this.EmailCode = emailCode;
            this.Username = username;
            this.Errors = errors;
        }

        public PasswordResetCodeResponseErrors Errors { get; }
        public string EmailCode { get; }
        public string Username { get; }
    }
}
