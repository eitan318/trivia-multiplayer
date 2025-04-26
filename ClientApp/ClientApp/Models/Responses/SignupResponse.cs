using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Responses
{
    class SignupResponse : Response
    {
        public ResponsesCodes GetCode() => ResponsesCodes.SignupResponse;
    }
}
