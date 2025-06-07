using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Stores
{
    class PasswordResetStore : StoreBase
    {
        private string _email;
        private string _resetCode;
        private string _newPassword;
        private string _passwordResetTocken;

        public string Email
        {
            get => _email;
            set
            {
                if (_email != value)
                {
                    _email = value;
                    OnPropertyChanged(nameof(Email));
                }
            }
        }

        public string ResetCode
        {
            get => _resetCode;
            set
            {
                if (_resetCode != value)
                {
                    _resetCode = value;
                    OnPropertyChanged(nameof(ResetCode));
                }
            }
        }

        public string NewPassword
        {
            get => _newPassword;
            set
            {
                if (_newPassword != value)
                {
                    _newPassword = value;
                    OnPropertyChanged(nameof(NewPassword));
                }
            }
        }

        
        public string Tocken
        {
            get => _passwordResetTocken;
            set
            {
                if (_passwordResetTocken != value)
                {
                    _passwordResetTocken = value;
                    OnPropertyChanged(nameof(Tocken));
                }
            }
        }

    }

}
