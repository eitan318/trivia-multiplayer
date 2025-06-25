using ClientApp.Models.ResponseErrors;
using Newtonsoft.Json;

namespace ClientApp.Models.Responses
{
    class GetQuestionResponse : Response<GeneralResponseErrors>
    {
        private GetQuestionResponse() { }


        [JsonProperty]


        public GetQuestionResponseData Data { get; private set; }
    }

}
