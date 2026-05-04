using ClientApp.Models.ResponseErrors;
using Newtonsoft.Json;

namespace ClientApp.Models.Responses
{
    class HighScoresResponse : Response<NoResponseErrors>
    {
        private HighScoresResponse() { }
        [JsonProperty]
        public List<HighScoreInfoModel> Statistics { get; private set; }


    }
}
