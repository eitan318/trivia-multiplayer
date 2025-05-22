
namespace ClientApp.ViewModels
{
    class ErrorViewModel : ViewModelBase
    {
        public string StatusMessage { get; }

        private ErrorViewModel(string initialMessage) { 
            StatusMessage = initialMessage;
        }
        public static ErrorViewModel Instance(string initialMessage)
        {
            return GetInstance(() => new ErrorViewModel(initialMessage));
        }

    }
}
