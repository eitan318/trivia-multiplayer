using ClientApp.Models.ResponseErrors;
using Newtonsoft.Json;
namespace ClientApp.Models.Responses
{
    class GetPlayersInRoomResponse : Response<NoResponseErrors>
    {
        private GetPlayersInRoomResponse() { }

        [JsonProperty]
        public List<LoggedUser> Players { get; private set; }
    }
}
