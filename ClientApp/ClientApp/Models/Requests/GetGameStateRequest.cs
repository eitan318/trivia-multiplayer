using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Requests
{
    class GetGameStateRequest : IRequest
    {
        public RequestsCodes GetCode() => RequestsCodes.GetGameStateRequrst;
    }
}
