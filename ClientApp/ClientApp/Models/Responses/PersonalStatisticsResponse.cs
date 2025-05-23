using Newtonsoft.Json;

namespace ClientApp.Models.Responses
{
    class PersonalStatisticsResponse : Response
    {
        private PersonalStatisticsResponse() {}
        public ResponsesCodes GetCode() => ResponsesCodes.GetPersonalStatsResponse;
        [JsonProperty]
        public PersonalStatisticsModel Statistics { get; private set; }
    }
}
