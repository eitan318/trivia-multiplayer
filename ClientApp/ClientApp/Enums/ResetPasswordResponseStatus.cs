using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Enums
{
    enum ResetPasswordResponseStatus
    {
        Success = 0,
        UnknowenUsername = 1,
        InvalidPassword = 2,
        InvalidUsername = 3
    }
}
