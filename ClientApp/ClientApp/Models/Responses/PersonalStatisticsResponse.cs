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
        public PersonalStatisticsResponse(uint status) : base(status) { }
        public ResponsesCodes GetCode() => ResponsesCodes.JoinRoomResponse;
        public JoinRoomResponseErrors Errors { get; }
    }
}
