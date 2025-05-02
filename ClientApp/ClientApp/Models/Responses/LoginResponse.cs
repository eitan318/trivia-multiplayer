using ClientApp.Models.ResponseErrors;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices.Marshalling;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Responses
{
    class LoginResponse : Response
    {
        [JsonConstructor]
        private LoginResponse(uint status, LoginResponseErrors errors) : base(status) {
            Errors = errors;
        }

        public LoginResponseErrors Errors { get; }
        public ResponsesCodes GetCode() => ResponsesCodes.LoginResponse;
    }
}
