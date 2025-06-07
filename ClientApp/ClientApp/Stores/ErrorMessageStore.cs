using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Stores
{
    public class ErrorMessageStore : StoreBase
    {
        private string _errorMessage;
        private string _errorType;

        public string ErrorMessage
        {
            get => _errorMessage;
            set
            {
                if (_errorMessage != value)
                {
                    _errorMessage = value;
                    OnPropertyChanged(nameof(ErrorMessage));
                }
            }
        }


        public string ErrorType
        {
            get => _errorType;
            set
            {
                if (_errorType != value)
                {
                    _errorType = value;
                    OnPropertyChanged(nameof(ErrorType));
                }
            }
        }
    }
}
