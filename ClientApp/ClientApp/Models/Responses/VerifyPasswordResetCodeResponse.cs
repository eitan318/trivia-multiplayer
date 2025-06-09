using ClientApp.Models.ResponseErrors;
using Newtonsoft.Json;

namespace ClientApp.Models.Responses {
    class VerifyPasswordResetCodeResponse : Response {
          private VerifyPasswordResetCodeResponse() {}

                
          [JsonProperty]
          public string  PasswordResetTocken { get; private set; }
          [JsonProperty]
          public VerifyPasswordResetCodeResponseErrors Errors { get; private set; }
          public override ResponsesCodes GetCode() => ResponsesCodes.VerifyPasswordCodeResponse;
    }
}
