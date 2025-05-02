using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Requests
{
    /// <summary>
    /// Represents a request for the top high scores
    /// /// </summary>
    class HighScoresRequest : IRequest
    {
        public HighScoresRequest(int topPlayersLimit)
        {
            this.TopPlayersLimit = topPlayersLimit;
        }
        public RequestsCodes GetCode() => RequestsCodes.GetHighScoresRequest;
        public int TopPlayersLimit;
    }
}
