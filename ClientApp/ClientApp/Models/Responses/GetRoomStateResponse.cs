using Newtonsoft.Json;

namespace ClientApp.Models.Responses
{
    class GetRoomStateResponse : Response
    {
        private GetRoomStateResponse() { }


        [JsonProperty]
        public RoomState RoomState{ get; private set; }
    }
}
