using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json.Serialization;
using System.Threading.Tasks;
using ClientApp.Models;

namespace ClientApp.Models.Responses
{
    class GetRoomsResponse : Response
    {
        [JsonConstructor]
        public GetRoomsResponse(uint status, List<RoomData> rooms) :base(status)
        { 
            this.Rooms = rooms;
        }
        public List<RoomData> Rooms { get; }
    }
}
