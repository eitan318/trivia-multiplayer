using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Responses
{
    class JoinRoomResponse : Response
    {
        [JsonConstructor]
        public JoinRoomResponse(uint status) : base(status) { }
        public ResponsesCodes GetCode() => ResponsesCodes.JoinRoomResponse;

    }
}
