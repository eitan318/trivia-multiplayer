using Newtonsoft.Json;

namespace ClientApp.Models.Responses
{
    class HighScoresResponse : Response
    {
        private HighScoresResponse() { }
        public ResponsesCodes GetCode() => ResponsesCodes.HighScoresRespones;

        [JsonProperty]
        public List<HighScoreInfo> Statistics { get; private set; }


    }
}
