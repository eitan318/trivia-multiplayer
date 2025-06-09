using Newtonsoft.Json;

namespace ClientApp.Models.Responses
{
    abstract class Response
    {
        [JsonProperty]
        public uint Status { get; private set; }

        public abstract ResponsesCodes GetCode();
    }
}
