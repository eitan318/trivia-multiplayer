using ClientApp.Models.ResponseErrors;
using Newtonsoft.Json;

namespace ClientApp.Models.Responses
{
    class CreateRoomResponse : Response<CreateRoomResponseErrors>
    {
        private CreateRoomResponse() { }
        [JsonProperty]
        public RoomDataModel RoomData { get; private set; }
    }
}
