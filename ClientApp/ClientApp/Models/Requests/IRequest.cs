
namespace ClientApp.Models.Requests
{
    /// <summary>
    /// Represents a general request 
    /// </summary>
    interface IRequest
    {
        public RequestsCodes GetCode();
    }
}
