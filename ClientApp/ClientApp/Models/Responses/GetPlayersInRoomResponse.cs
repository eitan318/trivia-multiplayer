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
        [JsonConstructor]
        public GetPlayersInRoomResponse(uint status, List<string> players) : base(status)
        {
            this.Players = players;
        }
        public List<string> Players { get; }
    }
}
