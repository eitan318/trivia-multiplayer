using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Requests
{
    /// <summary>
    /// Represents a request for logging out
    /// /// </summary>
    class LogoutRequest : IRequest
    {
        public RequestsCodes GetCode() => RequestsCodes.LogoutRequest;
    }
}
