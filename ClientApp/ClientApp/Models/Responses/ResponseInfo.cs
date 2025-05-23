
namespace ClientApp.Models.Responses
{
    class ResponseInfo<T> where T : Response
    {
        public ResponseInfo(bool success, T? response, ErrorResponse? errorResponse)
        {
            NormalResponse = success;
            Response = response;
            ErrorResponse = errorResponse;
        }
        public bool NormalResponse { get; }
        public T? Response { get; }
        public ErrorResponse? ErrorResponse { get; }
    }
}
