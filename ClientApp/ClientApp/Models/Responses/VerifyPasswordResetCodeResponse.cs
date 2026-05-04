using ClientApp.Models.ResponseErrors;
using Newtonsoft.Json;

namespace ClientApp.Models.Responses {
    class VerifyPasswordResetCodeResponse : Response<GeneralResponseErrors> {
          private VerifyPasswordResetCodeResponse() {}

                
          [JsonProperty]
          public string  PasswordResetTocken { get; private set; }
    }
}
