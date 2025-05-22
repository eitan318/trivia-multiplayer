using ClientApp.Services;
using ClientApp.Stores;
using System;
using System.Threading.Tasks;

namespace ClientApp.ViewModels
{
    public class MainWindowViewModel : ViewModelBase
    {
        private readonly NavigationStore _navigationStore;
        private readonly ErrorMessageStore _errorMessageStore;
        private readonly INavigationService _navigationService;

        public MainWindowViewModel(
            NavigationStore navigationStore,
            ErrorMessageStore errorMessageStore,
            INavigationService navigationService)
        {
            _navigationStore = navigationStore;
            _errorMessageStore = errorMessageStore;
            _navigationService = navigationService;

            _navigationStore.CurrentViewChanged += OnCurrentViewChanged;

            SocketService.Initialize("127.0.0.1", 5554);

            try
            {
                SocketService.Connect();
                _navigationService.NavigateTo<LoginViewModel>();
            }
            catch
            {
                AttemptConnectionAsync();
            }
        }

        private void OnCurrentViewChanged()
        {
            OnPropertyChanged(nameof(CurrentView));
        }

        public object CurrentView => _navigationStore.CurrentView;

        private async void AttemptConnectionAsync()
        {
            // Display the error page
            _errorMessageStore.ErrorMessage = "Connection Error";
            _errorMessageStore.ErrorType = "Unable to connect to Server. Trying...";
            _navigationService.NavigateTo<ErrorViewModel>();

            while (true)
            {
                try
                {
                    await Task.Run(() => SocketService.Connect());
                    break;
                }
                catch
                {
                    await Task.Delay(2000); // Wait for 2 seconds before retrying
                }
            }

            _navigationService.NavigateTo<LoginViewModel>();
        }
    }
}
