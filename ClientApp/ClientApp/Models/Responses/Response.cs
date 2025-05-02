using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ClientApp.Models.ResponseErrors;

namespace ClientApp.Models.Responses
{
    abstract class Response
    {
        public uint Status { get; private set; }
    }
}
