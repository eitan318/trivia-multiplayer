using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Enums
{
    enum LoginResponseStatus
    {
        Success = 0,
        UnknowenUsername = 1,
        PasswordDoesntMatch = 2
    };
}
