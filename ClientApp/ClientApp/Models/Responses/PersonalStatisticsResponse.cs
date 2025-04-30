using ClientApp.Models.ResponseErrors;
using Newtonsoft.Json;
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
        public PersonalStatisticsResponse(PersonalStatistics personalstats,uint status) : base(status)
        {
            this.PersonalStatistics = personalstats;
        }
        public ResponsesCodes GetCode() => ResponsesCodes.JoinRoomResponse;
        public PersonalStatistics PersonalStatistics { get; }
        public JoinRoomResponseErrors Errors { get; }
    }
}
