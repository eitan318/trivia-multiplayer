using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using System.Threading.Tasks;

namespace ClientApp.Services
{
    /// <summary>
    /// Provides services for exchanging requests with a server and handling responses.
    /// </summary>
    public class RequestsExchangeService
    {
        private readonly SocketService _socketService;

        public RequestsExchangeService(SocketService socketService)
        {
            _socketService = socketService;
        }

        internal async Task<ResponseInfo> ExchangeRequest(IRequest request)
        {
            byte[] requestData = JsonRequestSerializer.SerializeRequest(request);

            await _socketService.SendDataAsync(new ArraySegment<byte>(requestData));
            
            byte[] codeBuffer = await _socketService.ReceiveDataAsync(1);
            byte[] lengthBuffer = await _socketService.ReceiveDataAsync(4);
            int length = BitConverter.ToInt32(lengthBuffer, 0);
            byte[] payloadBuffer = await _socketService.ReceiveDataAsync(length);

            return new ResponseInfo(codeBuffer[0], payloadBuffer);
        }
    }
}
