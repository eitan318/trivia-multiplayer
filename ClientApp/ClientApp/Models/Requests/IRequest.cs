using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Requests
{
    interface IRequest
    {
        public RequestsCodes GetCode();
    }
}
