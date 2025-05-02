using ClientApp.Models.ResponseErrors;
using System.Text.Json.Serialization;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Responses
{
    class HighScoresResponse : Response
    {
        [JsonConstructor]
        public HighScoresResponse(uint status, List<HighScoreInfo> statistics) : base(status)
        {
            
            this.Statisics = statistics;
        }
        public List<HighScoreInfo> Statisics { get; }
        public ResponsesCodes GetCode() => ResponsesCodes.HighScoresRespones;

    }
}
