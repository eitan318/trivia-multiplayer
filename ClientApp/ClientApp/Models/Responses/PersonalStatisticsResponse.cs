using ClientApp.Models.ResponseErrors;
using System.Text.Json.Serialization;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace ClientApp.Models.Responses
{
    class PersonalStatisticsResponse : Response
    {
        private PersonalStatisticsResponse() {}
        public ResponsesCodes GetCode() => ResponsesCodes.GetPersonalStatsResponse;
        [JsonProperty]
        public PersonalStatistics Statistics { get; }
    }
}
