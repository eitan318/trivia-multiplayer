using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Enums
{
    enum SignupResponseStatus
    {
        Success = 0,
        KnowenUsername = 1,
        InvalidPassword = 2,
        InvalidEmailFormat = 3,
        InvalidHousAddress = 4,
        InvalidPhoneNumber = 5,
        InvalidBirthDate = 6

    }
}
