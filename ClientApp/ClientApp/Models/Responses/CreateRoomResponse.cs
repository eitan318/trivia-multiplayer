using ClientApp.Models.ResponseErrors;
using Newtonsoft.Json;

namespace ClientApp.Models.Responses
{
    class CreateRoomResponse : Response
    {
        private CreateRoomResponse() { }
        public ResponsesCodes GetCode() => ResponsesCodes.CreateRoomResponse;
        [JsonProperty]
        public RoomDataModel RoomData { get; private set; }
        [JsonProperty]
        public CreateRoomResponseErrors Errors { get; private set; }
    }
}
