using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Responses
{
    class GetPlayersInRoomResponse : Response
    {
        private GetPlayersInRoomResponse() { }
        [JsonProperty]
        public List<string> Players { get; private set; }
    }
}
