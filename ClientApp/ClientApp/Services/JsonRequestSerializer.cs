using ClientApp.Models.Requests;
using Newtonsoft.Json;
using System.Text;

namespace ClientApp.Services
{
    /// <summary>
    /// Provides serialization functionality for client requests into JSON format.
    /// </summary>
    public class JsonRequestSerializer
    {
        /// <summary>
        /// Serializes a request object into a byte array for transmission.
        /// The serialized format includes:
        /// 1. A single byte representing the request code.
        /// 2. Four bytes (big-endian) representing the length of the JSON data.
        /// 3. The JSON representation of the request.
        /// </summary>
        /// <param name="request">The request object implementing <see cref="IRequest"/> to be serialized.</param>
        /// <returns>A byte array containing the serialized request data.</returns>
        /// <remarks>
        /// - The JSON payload is encoded using UTF-8.
        /// - The length prefix ensures the server can correctly read the JSON payload.
        /// - The request code identifies the type of request.
        /// </remarks>
        /// <exception cref="ArgumentNullException">Thrown if the <paramref name="request"/> is null.</exception>
        internal byte[] SerializeRequest(IRequest request)
        {
            string json = JsonConvert.SerializeObject(request);
            byte[] jsonBytes = Encoding.UTF8.GetBytes(json);

            // Convert the length of the JSON bytes to a 4-byte array
            byte[] lengthBytes = BitConverter.GetBytes(jsonBytes.Length);
            if (!BitConverter.IsLittleEndian)
                Array.Reverse(lengthBytes); // Ensure little-endian format if needed

            var dataBytes = new byte[1 + lengthBytes.Length + jsonBytes.Length];
            dataBytes[0] = (byte)request.GetCode();
            Array.Copy(lengthBytes, 0, dataBytes, 1, lengthBytes.Length);
            Array.Copy(jsonBytes, 0, dataBytes, 1 + lengthBytes.Length, jsonBytes.Length);
            
            return dataBytes;
        }
        
        internal byte[] SerializeRequest(RequestsCodes code)
        {
            string json = "";
            byte[] jsonBytes = Encoding.UTF8.GetBytes(json);

            // Convert the length of the JSON bytes to a 4-byte array
            byte[] lengthBytes = BitConverter.GetBytes(jsonBytes.Length);
            if (!BitConverter.IsLittleEndian)
                Array.Reverse(lengthBytes); // Ensure little-endian format if needed

            var dataBytes = new byte[1 + lengthBytes.Length + jsonBytes.Length];
            dataBytes[0] = (byte)code;
            Array.Copy(lengthBytes, 0, dataBytes, 1, lengthBytes.Length);
            Array.Copy(jsonBytes, 0, dataBytes, 1 + lengthBytes.Length, jsonBytes.Length);
            
            return dataBytes;
        }

    }
}
