using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Responses
{
    class ResetPasswordResponse : Response
    {
        public ResponsesCodes GetCode() => ResponsesCodes.ResetPasswordResponse;
    }
}
