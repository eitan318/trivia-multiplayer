using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models
{
    class RoomState
    {
        [JsonProperty]
        public RoomStatus RoomStatus { get; private set; }

        [JsonProperty]
        public uint AnswerCount { get; private set; }

        [JsonProperty]
        public double AnswerTimeOut { get; private set; }

        [JsonProperty]
        public List<LoggedUser> Players { get; private set; }
    };

}
