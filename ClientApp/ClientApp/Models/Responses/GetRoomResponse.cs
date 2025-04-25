using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ClientApp.Models;

namespace ClientApp.Models.Responses
{
    public class GetRoomResponse
    {
        public int Status { get; set; }
        public List<RoomData> Rooms;
    }
}
