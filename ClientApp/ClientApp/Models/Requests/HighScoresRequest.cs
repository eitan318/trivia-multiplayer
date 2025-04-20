using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Requests
{
    class HighScoresRequest : IRequest
    {
        public RequestsCodes GetCode() => RequestsCodes.HighScoresRequest;
    }
}
