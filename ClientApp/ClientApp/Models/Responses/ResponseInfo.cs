using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Responses
{
    public struct ResponseInfo
    {
        //public ResponseInfo(byte code, byte[] buffer)
        //{
        //    Code = code; 
        //    Buffer = buffer;
        //}
        public byte Code { get; set; }
        public byte[] Buffer { get; set; }
    }
}
