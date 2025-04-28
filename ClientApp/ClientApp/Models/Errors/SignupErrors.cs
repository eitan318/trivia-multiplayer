using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Errors
{
    class SignupErrors
    {
        public string UsernameError { get; set; }
        public string PasswordError { get; set; }
        public string EmailError { get; set; }
        public string PhoneNumberError { get; set; }
        public string HouseAddressError { get; set; }
        public string BirthDateError { get; set; }
    }
}
