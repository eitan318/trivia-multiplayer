using Newtonsoft.Json;

namespace ClientApp.Models.Responses
{
    class GetRoomStateResponse : Response
    {
        private GetRoomStateResponse() { }
        public override ResponsesCodes GetCode() => ResponsesCodes.GetRoomStateRespones;


        [JsonProperty]
        public RoomState RoomState{ get; private set; }
    }
}
