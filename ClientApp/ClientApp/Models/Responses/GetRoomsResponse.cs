using Newtonsoft.Json;
using ClientApp.Models.ResponseErrors;
namespace ClientApp.Models.Responses
{
    class GetRoomsResponse : Response<NoResponseErrors>
    {
        private GetRoomsResponse() { }

        [JsonProperty]
        public List<RoomPreview> Rooms { get; private set; }
    }
}
