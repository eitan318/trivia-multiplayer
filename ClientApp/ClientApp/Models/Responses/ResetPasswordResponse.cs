using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ClientApp.Models.ResponseErrors;
using Newtonsoft.Json;

namespace ClientApp.Models.Responses
{
    class ResetPasswordResponse : Response
    {
        private ResetPasswordResponse() { }
        [JsonProperty]
        public ResetPasswordErrors Errors { get; private set; }
        public ResponsesCodes GetCode() => ResponsesCodes.ResetPasswordResponse;
    }
}
