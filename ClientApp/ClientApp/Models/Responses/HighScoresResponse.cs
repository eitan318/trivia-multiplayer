using ClientApp.Models.ResponseErrors;
using Newtonsoft.Json;
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
        public HighScoresResponse(uint status, List<HighScoreInfo> highscores) : base(status)
        {
            
            this.HighScores = highscores;
        }
        public List<HighScoreInfo> HighScores { get; set; }
        public ResponsesCodes GetCode() => ResponsesCodes.HighScoresRespones;

    }
}
