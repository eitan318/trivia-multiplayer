using Newtonsoft.Json;
namespace ClientApp.Models.Responses
{
    class GetPlayersInRoomResponse : Response
    {
        private GetPlayersInRoomResponse() { }
        [JsonProperty]
        public List<LoggedUser> Players { get; private set; }
    }
}
