using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.ResponseErrors
{
    class LoginResponseErrors
    {
        public string UsernameError { get; set; }
        public string PasswordError { get; set; }
        public string GeneralError { get; set; }
    }
}
