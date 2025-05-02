using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ClientApp.Models.ResponseErrors;
using Newtonsoft.Json;

namespace ClientApp.Models.Responses
{
    class SignupResponse : Response
    {
        private SignupResponse() { }
        [JsonProperty]
        public SignupErrors Errors { get; private set; }
        public ResponsesCodes GetCode() => ResponsesCodes.SignupResponse;
    }
}
