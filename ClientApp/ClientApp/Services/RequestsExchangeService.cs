using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Stores;
using System.Net.Sockets;

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
        private readonly ServerErrorMessageStore _errorMessageStore;

        public RequestsExchangeService(SocketService socketService, 
            JsonResponseDeserializer responseDiserializer,
            JsonRequestSerializer requestSerializer,
            ServerErrorMessageStore errorMessageStore)
        {
            this._errorMessageStore = errorMessageStore;
            this._requestSerializer = requestSerializer;
            this._responseDiserializer = responseDiserializer;
            _socketService = socketService;
        }

        internal async Task<ResponseInfo<T>> ExchangeRequest<T>(IRequest request) where T : class 
        {    
            byte[] requestData = _requestSerializer.SerializeRequest(request);

            byte[] codeBuffer = null;
            byte[] payloadBuffer = null;
            try
            {
                await _socketService.SendDataAsync(new ArraySegment<byte>(requestData));
                
                codeBuffer = await _socketService.ReceiveDataAsync(1);
                byte[] lengthBuffer = await _socketService.ReceiveDataAsync(4);
                int length = BitConverter.ToInt32(lengthBuffer, 0);
                payloadBuffer = await _socketService.ReceiveDataAsync(length);
            }
            catch (SocketException ex)
            {
                // Handle socket-related exceptions
                _errorMessageStore.ErrorMessage = $"Connection error: {ex.Message}";
                return new ResponseInfo<T>(false, null, new ErrorResponse(ex.Message));
            }


            byte code = codeBuffer[0];

            bool success = (byte)ResponsesCodes.ErrorResponse != code;

            if (success)
            {
                return new ResponseInfo<T>(success, this._responseDiserializer.DeserializeResponse<T>(payloadBuffer, code), null);
            }
            else 
            {
                ErrorResponse errorResponse = this._responseDiserializer.DeserializeResponse<ErrorResponse>(payloadBuffer, code);
                this._errorMessageStore.ErrorMessage = "SERVER ERROR: " + errorResponse.Message;
                return new ResponseInfo<T>(success, null, errorResponse);
            }
            
        }
    }
}
