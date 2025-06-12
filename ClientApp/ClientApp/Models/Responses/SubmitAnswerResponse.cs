using ClientApp.Models.ResponseErrors;
using Newtonsoft.Json;
namespace ClientApp.Models.Responses
{
    class SubmitAnswerResponse : Response
    {
        private SubmitAnswerResponse() { }

        public override ResponsesCodes GetCode() => ResponsesCodes.SubmitAnswerResponse;

        [JsonProperty]
        public uint CorrectAnswerId { get; private set; }
       
        [JsonProperty]
        public int AnswerScore { get; private set; }

        [JsonProperty]
        public GeneralResponseErrors Errors { get; private set; }
    }
}
