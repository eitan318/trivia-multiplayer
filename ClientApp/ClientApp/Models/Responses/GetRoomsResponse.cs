using Newtonsoft.Json;
namespace ClientApp.Models.Responses
{
    class GetRoomsResponse : Response
    {
        private GetRoomsResponse() { }


        public override ResponsesCodes GetCode() => ResponsesCodes.GetRoomsResponse;


        [JsonProperty]
        public List<RoomPreview> Rooms { get; private set; }
    }
}
