using Newtonsoft.Json;
namespace ClientApp.Models.Responses
{
    class GetPlayersInRoomResponse : Response
    {
        private GetPlayersInRoomResponse() { }
        public override ResponsesCodes GetCode() => ResponsesCodes.GetPlayersInRoomResponse;

        [JsonProperty]
        public List<LoggedUser> Players { get; private set; }
    }
}
