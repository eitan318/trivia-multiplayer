using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace ClientApp.Models.Responses
{
    class SignupResponse : Response
    {
        [JsonConstructor]
        public SignupResponse(uint status) : base(status) { }
        public bool[] RegexResult { get; }
        public ResponsesCodes GetCode() => ResponsesCodes.SignupResponse;
    }
}
