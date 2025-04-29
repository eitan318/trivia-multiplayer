using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace ClientApp.Models.Responses
{
    class LogoutResponse : Response
    {
        [JsonConstructor]
        public LogoutResponse(uint status) : base(status) { }
        public ResponsesCodes GetCode() => ResponsesCodes.LogoutResponse;
    }
}
