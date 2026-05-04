using ClientApp.Models.ResponseErrors;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Responses
{
    class Get1v1GameSettingsResponse : Response<GeneralResponseErrors>
    {
        private Get1v1GameSettingsResponse() { }

        [JsonProperty]
        public RoomDataModel GameSettigns { get; private set; }
    }
}
