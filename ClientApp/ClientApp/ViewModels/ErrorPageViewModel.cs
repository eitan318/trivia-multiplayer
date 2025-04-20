using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.ViewModels
{
    using System.ComponentModel;
    using System.Runtime.CompilerServices;
    using System.Windows.Controls;

    namespace ClientApp.ViewModels
    {
        class ErrorPageViewModel : BaseViewModel
        {
            public string StatusMessage { get; }

            private ErrorPageViewModel(string initialMessage) { 
                StatusMessage = initialMessage;
            }
            public static ErrorPageViewModel Instance(string initialMessage)
            {
                return GetInstance(() => new ErrorPageViewModel(initialMessage));
            }

        }
    }

}
