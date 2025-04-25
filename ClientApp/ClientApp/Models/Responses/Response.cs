using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Responses
{
    abstract class Response
    {
        public uint Status {  get; set; }
    }
}
