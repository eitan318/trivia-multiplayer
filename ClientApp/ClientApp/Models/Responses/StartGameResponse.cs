
namespace ClientApp.Models.Responses
{
    class StartGameResponse : Response
    {
        private StartGameResponse() { }
        public ResponsesCodes GetCode() => ResponsesCodes.StartGameResponse;
    }
}
