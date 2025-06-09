using ClientApp.Models.ResponseErrors;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Responses
{
    class CloseRoomResponse : Response
    {
        private CloseRoomResponse() { }
        
        [JsonProperty]
        public CloseRoomResponseErrors Errors { get; private set; }
        public override ResponsesCodes GetCode() => ResponsesCodes.CloseRoomResponse;
    }
}
