using ClientApp.Models.ResponseErrors;
using Newtonsoft.Json;

namespace ClientApp.Models.Responses
{
    class GetRoomStateResponse : Response<NoResponseErrors>
    {
        private GetRoomStateResponse() { }

        [JsonProperty]
        public RoomState RoomState{ get; private set; }
    }
}
