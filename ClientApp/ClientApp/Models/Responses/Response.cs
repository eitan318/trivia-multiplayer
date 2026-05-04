using Newtonsoft.Json;

namespace ClientApp.Models.Responses
{
    abstract class Response<TError>
    {
        [JsonProperty]
        public uint Status { get; private set; }

        [JsonProperty]
        public TError Errors { get; private set; }

        [JsonIgnore]
        public ResponsesCodes Code { get; private set; }

        protected Response()
        {
        }
    }
    abstract class Response<TError, TData> : Response<TError>
    {
        [JsonProperty("Data")]
        public TData Data { get; private set; }

        public Response() { }
    }


}
