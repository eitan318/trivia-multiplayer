using ClientApp.Models.ResponseErrors;
using Newtonsoft.Json;

namespace ClientApp.Models.Responses
{
    class GetQuestionResponse : Response<NoResponseErrors>
    {
        private GetQuestionResponse() { }

        [JsonProperty]
        public QuestionInfo Question { get; private set; }
    }
}
