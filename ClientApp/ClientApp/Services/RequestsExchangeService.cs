using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Services
{
    class RequestsExchangeService
    {
        public static async Task<ResponseInfo> ExchangeRequest(IRequest request)
        {
            byte[] requestData = JsonRequestSerializer.SerializeRequest(request);
            await SocketService.SendDataAsync(requestData);

            byte[] codeBuffer = await SocketService.ReceiveDataAsync(1);
            byte[] lengthBuffer = await SocketService.ReceiveDataAsync(4);
            int length = BitConverter.ToInt32(lengthBuffer, 0);
            byte[] payloadBuffer = await SocketService.ReceiveDataAsync(length);
            return new ResponseInfo
            {
                Code = codeBuffer[0],
                Buffer = payloadBuffer
            };
        }
    }
}
