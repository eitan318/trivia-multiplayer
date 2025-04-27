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
        public CreateRoomResponse(uint status, CreateRoomErros errors, RoomData roomData) : base(status){
            this.RoomData = roomData;
            this.Errors = errors;
        }
        public ResponsesCodes GetCode() => ResponsesCodes.CreateRoomResponse;
        public RoomData RoomData { get; }
        public CreateRoomErros Errors { get; }
    }
}
