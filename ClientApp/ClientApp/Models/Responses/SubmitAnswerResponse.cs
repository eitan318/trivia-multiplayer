using ClientApp.Models.ResponseErrors;
using Newtonsoft.Json;
namespace ClientApp.Models.Responses
{
    class SubmitAnswerResponse : Response<GeneralResponseErrors>
    {
        private SubmitAnswerResponse() { }

        [JsonProperty]
        public uint CorrectAnswerId { get; private set; }
       
        [JsonProperty]
        public int AnswerScore { get; private set; }

    }
}
