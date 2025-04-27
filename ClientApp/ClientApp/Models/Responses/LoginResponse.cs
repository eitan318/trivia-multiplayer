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
        public LoginResponse(uint status, LoginErrors errors) : base(status) {
            Errors = errors;
        }

        public LoginErrors Errors { get; }
        public ResponsesCodes GetCode() => ResponsesCodes.LoginResponse;
    }
}
