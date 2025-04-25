using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Responses
{
    class CreateRoomResponse : Response
    {
        public ResponsesCodes GetCode() => ResponsesCodes.CreateRoomResponse;
        public uint RoomId { get; set; }
    }
}
