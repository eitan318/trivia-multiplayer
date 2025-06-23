using ClientApp.Models.ResponseErrors;
using Newtonsoft.Json;

namespace ClientApp.Models.Responses
{
    class GetGameResultsResponse : Response<NoResponseErrors>
    {
        private GetGameResultsResponse() { }

        [JsonProperty]
        public List<PlayerResults> Results { get; private set; }

    }
}
