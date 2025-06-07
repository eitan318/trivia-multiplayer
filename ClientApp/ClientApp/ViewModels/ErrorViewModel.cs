using ClientApp.Stores;

namespace ClientApp.ViewModels
{
    class ErrorViewModel : ViewModelBase
    {
        private ErrorMessageStore _errorMessageStore;

        public ErrorViewModel(ErrorMessageStore errorMessageStore) {
            this._errorMessageStore = errorMessageStore;
        }

        public string StatusMessage
        {
            get => _errorMessageStore.ErrorMessage;
            set
            {
                _errorMessageStore.ErrorMessage = value;
                OnPropertyChanged();
            }
        }

    }
}
