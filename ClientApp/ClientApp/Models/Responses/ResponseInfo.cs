using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Responses
{
    class ResponseInfo
    {
        public ResponseInfo(byte code, byte[] buffer)
        {
            Code = code;
            Buffer = buffer;
        }
        public byte Code { get; }
        public byte[] Buffer { get; }
    }
}
