using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Requests
{
    /// <summary>
    /// Represents a request for getting data of all rooms
    /// /// /// </summary>
    class GetRoomsRequest : IRequest
    {
        public RequestsCodes GetCode() => RequestsCodes.GetRoomsRequest;
    }
}
