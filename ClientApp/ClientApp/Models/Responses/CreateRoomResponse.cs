using ClientApp.Models.ResponseErrors;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Responses
{
    class CreateRoomResponse : Response
    {
        private CreateRoomResponse() { }
        public ResponsesCodes GetCode() => ResponsesCodes.CreateRoomResponse;
        [JsonProperty]
        public RoomData RoomData { get; private set; }
        [JsonProperty]
        public CreateRoomResponseErros Errors { get; private set; }
    }
}
