using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Services
{
    /// <summary>
    /// Provides services for exchanging requests with a server and handling responses.
    /// </summary>
    class RequestsExchangeService
    {
        /// <summary>
        /// Sends a request to the server and receives the corresponding response.
        /// </summary>
        /// <param name="request">The request to be sent, implementing the <see cref="IRequest"/> interface.</param>
        /// <returns>
        /// A task representing the asynchronous operation. 
        /// The task result contains the <see cref="ResponseInfo"/> object, which includes the response code and payload.
        /// </returns>
        /// <exception cref="InvalidOperationException">Thrown if the socket is not connected.</exception>
        /// <exception cref="SocketException">Thrown if the connection is reset or closed by the server.</exception>
        public static async Task<ResponseInfo> ExchangeRequest(IRequest request)
        {
            // Serialize the request to bytes
            byte[] requestData = JsonRequestSerializer.SerializeRequest(request);

            // Send the serialized request to the server
            await SocketService.SendDataAsync(requestData);

            // Receive the response code (1 byte)
            byte[] codeBuffer = await SocketService.ReceiveDataAsync(1);

            // Receive the length of the response payload (4 bytes)
            byte[] lengthBuffer = await SocketService.ReceiveDataAsync(4); //Little endian
            int length = BitConverter.ToInt32(lengthBuffer, 0);

            // Receive the response payload based on the length
            byte[] payloadBuffer = await SocketService.ReceiveDataAsync(length);

            // Return the response information as a ResponseInfo object
            return new ResponseInfo( codeBuffer[0], payloadBuffer);
        }
    }
}
