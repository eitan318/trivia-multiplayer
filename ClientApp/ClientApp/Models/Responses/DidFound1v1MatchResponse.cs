using ClientApp.Models.ResponseErrors;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Responses
{
    class DidFound1v1MatchResponse : Response<GeneralResponseErrors>
    {
        private DidFound1v1MatchResponse() { }

        [JsonProperty]
        public bool FoundMatch {  get; private set; }
    }
}
