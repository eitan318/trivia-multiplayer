using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Requests
{
    class GetRoomStateRequest
    {
        public RequestsCodes GetCode() => RequestsCodes.GetRoomsRequest;

    }
}
