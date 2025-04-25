using App.Metrics.Health.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp
{
    class RegexFormats
    {
        public static readonly string Password = "must be 8+ chars, include upper/lower letters, digit, special char.";
        public static readonly string Email = "Use: Street, Apt, City";
        public static readonly string PhoneNumber = "0X(X)-XXXXXXX";
        public static readonly string Date = " DD.MM.YYYY or DD/MM/YYYY";

    }
}
