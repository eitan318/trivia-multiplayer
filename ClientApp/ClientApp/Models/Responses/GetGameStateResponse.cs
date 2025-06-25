using ClientApp.Models.ResponseErrors;
using Newtonsoft.Json;

namespace ClientApp.Models.Responses
{
    class GetGameStateResponse : Response<NoResponseErrors>
    {
        private GetGameStateResponse() { }

        [JsonProperty]
        public GameStatus GameStatus { get; private set; }
    }
}
