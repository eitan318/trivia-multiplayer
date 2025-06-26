using ClientApp.Commands;
using ClientApp.Services;
using ClientApp.Stores;
using System.Windows.Input;

namespace ClientApp.ViewModels
{
    public class MainWindowViewModel : ScreenViewModelBase
    {
        private readonly NavigationStore _navigationStore;
        private readonly ServerErrorMessageStore _errorMessageStore;
        private readonly INavigationService _navigationService;
        private readonly SocketService _socketService;

        public MainWindowViewModel(
            NavigationStore navigationStore,
            ServerErrorMessageStore errorMessageStore,
            INavigationService navigationService,
            RequestsExchangeService requestsExchangeService,
            SocketService socketService)
        {
            _navigationStore = navigationStore;
            _errorMessageStore = errorMessageStore;
            _navigationService = navigationService;
            _socketService = socketService;

            // Bind event handlers
            _navigationStore.CurrentViewModelChanged += OnCurrentViewModelChanged;
            _errorMessageStore.PropertyChanged += (sender, args) =>
            {
                if (args.PropertyName == nameof(ServerErrorMessageStore.ErrorMessage))
                {
                    OnPropertyChanged(nameof(ServerErrorMessage));
                }
            };
        }

        public ICommand BackCmd => new RelayCommand(
            _ => _navigationService.GoBack()
        );

        public bool WindowBackBtn =>
            _navigationService.CanGoBack() && _navigationStore.CurrentViewModel?.WindowBackBtn == true;

        public bool NavBarBackBtn =>
            _navigationService.CanGoBack() && _navigationStore.CurrentViewModel?.NavBarBackBtn == true;

        public ScreenViewModelBase CurrentViewModel => _navigationStore.CurrentViewModel;

        public string ServerErrorMessage => _errorMessageStore.ErrorMessage;

        public void Initialize()
        {
            try
            {
                _socketService.Connect();
                _navigationService.NavigateTo<LoginViewModel>();
            }
            catch
            {
                AttemptConnectionAsync();
            }
        }

        private void OnCurrentViewModelChanged()
        {
            OnPropertyChanged(nameof(CurrentViewModel));
            OnPropertyChanged(nameof(WindowBackBtn));
            OnPropertyChanged(nameof(NavBarBackBtn));
        }

        private async void AttemptConnectionAsync()
        {
            // Display the error page
            _errorMessageStore.ErrorType = "Connection Error";
            _errorMessageStore.ErrorMessage = "Unable to connect to the server. Retrying...";
            _navigationService.NavigateTo<ErrorViewModel>();

            while (true)
            {
                try
                {
                    await Task.Run(() => _socketService.Connect());
                    break;
                }
                catch
                {
                    await Task.Delay(2000); // Wait for 2 seconds before retrying
                }
            }

            // Clear the error message and navigate to login
            _errorMessageStore.ErrorType = string.Empty;
            _errorMessageStore.ErrorMessage = string.Empty;
            _navigationService.NavigateTo<LoginViewModel>();
        }

        internal void OnWindowClosed()
        {
            // Cleanup resources
            _socketService.CloseConnection();

            // Unsubscribe event handlers to prevent memory leaks
            _navigationStore.CurrentViewModelChanged -= OnCurrentViewModelChanged;
        }
    }
}
