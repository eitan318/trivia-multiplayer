using Newtonsoft.Json;
using ClientApp.Models.ResponseErrors;
namespace ClientApp.Models.Responses
{
    class PersonalStatisticsResponse : Response<NoResponseErrors>
    {
        private PersonalStatisticsResponse() {}
        [JsonProperty]
        public PersonalStatisticsResponseData Statistics { get; private set; }
    }



}
