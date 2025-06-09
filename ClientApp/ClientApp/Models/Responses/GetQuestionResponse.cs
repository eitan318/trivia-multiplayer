using Newtonsoft.Json;

namespace ClientApp.Models.Responses
{
    class GetQuestionResponse : Response
    {
        private GetQuestionResponse() { }

        public override ResponsesCodes GetCode() => ResponsesCodes.GetQuestionResponse;


        [JsonProperty]
        public QuestionInfo Question { get; private set; }
    }
}
