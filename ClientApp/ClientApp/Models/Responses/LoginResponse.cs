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
        private LoginResponse() { }
        [JsonProperty]
        public LoginResponseErrors Errors { get; private set; }
        public ResponsesCodes GetCode() => ResponsesCodes.LoginResponse;
    }
}
