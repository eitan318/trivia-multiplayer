using Newtonsoft.Json;
namespace ClientApp.Models.Responses
{
    class GetRoomsResponse : Response
    {
        private GetRoomsResponse() { }
        [JsonProperty]
        public List<RoomPreview> Rooms { get; private set; }
    }
}
