using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models
{
    class PersonalStatisticsResponseData
    {
        [JsonProperty]
        public PersonalStatisticsModel RegularStats { get; private set; }
        [JsonProperty]
        public PersonalStatisticsModel Stats1v1 { get; private set; }
    }
}
