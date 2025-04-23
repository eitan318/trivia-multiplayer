using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Requests
{
    /// <summary>
    /// Represents a request for getting players in room
    /// /// </summary>
    class GetPlayersRequest : IRequest
    {
        public RequestsCodes GetCode() => RequestsCodes.GetPlayersRequest;
    }
}
