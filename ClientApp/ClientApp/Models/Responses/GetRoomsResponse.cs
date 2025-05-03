using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json.Serialization;
using System.Threading.Tasks;
using ClientApp.Models;
using Newtonsoft.Json;

namespace ClientApp.Models.Responses
{
    class GetRoomsResponse : Response
    {
        private GetRoomsResponse() { }
        [JsonProperty]
        public List<RoomPreview> Rooms { get; private set; }
    }
}
