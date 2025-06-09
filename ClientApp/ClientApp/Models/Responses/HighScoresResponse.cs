using Newtonsoft.Json;

namespace ClientApp.Models.Responses
{
    class HighScoresResponse : Response
    {
        private HighScoresResponse() { }
        public override ResponsesCodes GetCode() => ResponsesCodes.HighScoresRespones;

        [JsonProperty]
        public List<HighScoreInfoModel> Statistics { get; private set; }


    }
}
