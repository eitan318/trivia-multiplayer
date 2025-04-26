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
        [JsonConstructor]
        private CreateRoomResponse(uint status, uint roomId) : base(status){
            this.RoomId = roomId;
        }
        public ResponsesCodes GetCode() => ResponsesCodes.CreateRoomResponse;
        public uint RoomId { get; }
    }
}
