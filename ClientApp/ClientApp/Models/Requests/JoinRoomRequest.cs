using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Requests
{
    class JoinRoomRequest : IRequest
    {
        public uint RoomId { get; }
        public JoinRoomRequest (uint roomid)
        {
            RoomId = roomid;
        }
        public RequestsCodes GetCode() => RequestsCodes.JoinRoomRequest;
    }
}
