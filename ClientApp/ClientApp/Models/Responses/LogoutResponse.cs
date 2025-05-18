
namespace ClientApp.Models.Responses
{
    class LogoutResponse : Response
    {
        private LogoutResponse() { }
        public ResponsesCodes GetCode() => ResponsesCodes.LogoutResponse;
    }
}
