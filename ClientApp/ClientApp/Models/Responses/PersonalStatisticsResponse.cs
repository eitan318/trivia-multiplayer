using ClientApp.Models.ResponseErrors;
using System.Text.Json.Serialization;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ClientApp.Models.ResponseErrors;

namespace ClientApp.Models.Responses
{
    class PersonalStatisticsResponse : Response
    {
        [JsonConstructor]
        public PersonalStatisticsResponse(uint status, PersonalStatistics statistics) : base(status)
        {
            this.Statistics = statistics;
        }
        public ResponsesCodes GetCode() => ResponsesCodes.GetPersonalStatsResponse;
        public PersonalStatistics Statistics { get; }
    }
}
