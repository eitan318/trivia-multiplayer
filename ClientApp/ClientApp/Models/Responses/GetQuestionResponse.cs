using ClientApp.Models.ResponseErrors;
using Newtonsoft.Json;

namespace ClientApp.Models.Responses
{
    class GetQuestionResponse : Response<GeneralResponseErrors>
    {
        private GetQuestionResponse() { }

        [JsonProperty]
        public QuestionInfo Question { get; private set; }
        [JsonProperty]
        public uint QuestionNumber { get; private set; }
    }
}
