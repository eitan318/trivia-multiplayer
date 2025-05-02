using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ClientApp.Models.ResponseErrors;

namespace ClientApp.Models.Responses
{
    class JoinRoomResponse : Response
    {
        private JoinRoomResponse() { }
        public ResponsesCodes GetCode() => ResponsesCodes.JoinRoomResponse;
        [JsonProperty]
        public JoinRoomResponseErrors Errors { get; private set; }

    }
}
