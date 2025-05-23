
namespace ClientApp.Models.Responses
{
    public class ResponseInfo
    {
        public ResponseInfo(byte code, byte[] buffer)
        {
            Code = code;
            Buffer = buffer;
        }
        public byte Code { get; }
        public byte[] Buffer { get; }
    }
}
