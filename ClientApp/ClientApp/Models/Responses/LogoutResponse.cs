
namespace ClientApp.Models.Responses
{
    class LogoutResponse : Response
    {
        private LogoutResponse() { }
        public  override ResponsesCodes GetCode() => ResponsesCodes.LogoutResponse;
    }
}
