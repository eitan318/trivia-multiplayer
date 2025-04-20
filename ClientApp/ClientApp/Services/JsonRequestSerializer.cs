using ClientApp.Models.Requests;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Services
{
    class JsonRequestSerializer
    {
        static public byte[] SerializeRequest(IRequest request)
        {
            string json = JsonConvert.SerializeObject(request);
            byte[] jsonBytes = Encoding.UTF8.GetBytes(json);

            // Convert the length of the JSON bytes to a 4-byte array
            byte[] lengthBytes = BitConverter.GetBytes(jsonBytes.Length);
            if (BitConverter.IsLittleEndian)
                Array.Reverse(lengthBytes); // Ensure big-endian format if needed

            var dataBytes = new byte[1 + lengthBytes.Length + jsonBytes.Length];
            dataBytes[0] = (byte)request.GetCode();
            Array.Copy(lengthBytes, 0, dataBytes, 1, lengthBytes.Length);
            Array.Copy(jsonBytes, 0, dataBytes, 1 + lengthBytes.Length, jsonBytes.Length);
            
            return dataBytes;
        }
        

    }
}
