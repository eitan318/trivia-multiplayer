using ClientApp.Stores;

namespace ClientApp.ViewModels
{
    class ErrorViewModel : ScreenViewModelBase
    {
        private ServerErrorMessageStore _errorMessageStore;

        public ErrorViewModel(ServerErrorMessageStore errorMessageStore) {
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
