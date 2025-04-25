using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Requests
{
    class JoinRoomRequest : IRequest
    {
        private uint roomId;
        public JoinRoomRequest (uint roomid)
        {
            roomId = roomid;
        }
        public RequestsCodes GetCode() => RequestsCodes.JoinRoomRequest;
    }
}
