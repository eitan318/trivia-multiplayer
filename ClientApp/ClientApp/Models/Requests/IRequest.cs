using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Requests
{
    /// <summary>
    /// Represents a general request 
    /// </summary>
    interface IRequest
    {
        public RequestsCodes GetCode();
    }
}
