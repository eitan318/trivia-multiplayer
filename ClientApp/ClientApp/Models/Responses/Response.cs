using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Responses
{
    abstract class Response
    {
        [JsonConstructor]
        protected Response(uint status)
        {
            this.Status = status;
        }
        public uint Status {  get; }
    }
}
