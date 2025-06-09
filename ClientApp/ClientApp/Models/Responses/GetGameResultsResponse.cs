using Newtonsoft.Json;

namespace ClientApp.Models.Responses
{
    class GetGameResultsResponse : Response
    {
        private GetGameResultsResponse() { }

        [JsonProperty]
        public List<PlayerResults> Results { get; private set; }

        public override ResponsesCodes GetCode() => ResponsesCodes.GetGameResultsResponse;
    }
}
