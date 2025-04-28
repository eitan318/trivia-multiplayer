using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ClientApp.Models.Errors;
using Newtonsoft.Json;

namespace ClientApp.Models.Responses
{
    class ResetPasswordResponse : Response
    {
        [JsonConstructor]
        public ResetPasswordResponse(uint status, ResetPasswordErrors errors) : base(status) {
            this.Errors = errors;
        }

        public ResetPasswordErrors Errors { get; } 
        public ResponsesCodes GetCode() => ResponsesCodes.ResetPasswordResponse;
    }
}
