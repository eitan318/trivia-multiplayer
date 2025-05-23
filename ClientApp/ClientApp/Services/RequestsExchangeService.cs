using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using System.Threading.Tasks;

namespace ClientApp.Services
{
    /// <summary>
    /// Provides services for exchanging requests with a server and handling responses.
    /// </summary>
    internal class RequestsExchangeService
    {
        private readonly SocketService _socketService;
        private readonly JsonResponseDeserializer _responseDiserializer;
        private readonly JsonRequestSerializer _requestSerializer;

        public RequestsExchangeService(SocketService socketService, 
            JsonResponseDeserializer responseDiserializer,
            JsonRequestSerializer requestSerializer)
        {
            this._requestSerializer = requestSerializer;
            this._responseDiserializer = responseDiserializer;
            _socketService = socketService;
        }

        internal async Task<ResponseInfo<T>> ExchangeRequest<T>(IRequest request) where T : Response
        {
            byte[] requestData = _requestSerializer.SerializeRequest(request);

            await _socketService.SendDataAsync(new ArraySegment<byte>(requestData));
            
            byte[] codeBuffer = await _socketService.ReceiveDataAsync(1);
            byte[] lengthBuffer = await _socketService.ReceiveDataAsync(4);
            int length = BitConverter.ToInt32(lengthBuffer, 0);
            byte[] payloadBuffer = await _socketService.ReceiveDataAsync(length);

            byte code = codeBuffer[0];

            bool success = (byte)ResponsesCodes.ErrorResponse != code;

            if (success)
            {
                return new ResponseInfo<T>(success, this._responseDiserializer.DeserializeResponse<T>(payloadBuffer), null);
            }
            else 
            {
                return new ResponseInfo<T>(success, null, this._responseDiserializer.DeserializeResponse<ErrorResponse>(payloadBuffer));
            }
            
        }
    }
}
