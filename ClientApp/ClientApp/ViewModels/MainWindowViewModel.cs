using ClientApp.Commands;
using ClientApp.Services;
using ClientApp.Stores;
using System.Windows.Input;
using System.Windows.Navigation;

namespace ClientApp.ViewModels
{
    internal class MainWindowViewModel : ScreenViewModelBase
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
            _socketService = socketService;
            _navigationStore = navigationStore;
            _errorMessageStore = errorMessageStore;
            _navigationService = navigationService;

            
        }

        public void Initialize()
        {
            _navigationStore.CurrentViewModelChanged += OnCurrentViewModelChanged;

            _errorMessageStore.PropertyChanged += (sender, args) =>
            {
                if (args.PropertyName == nameof(ServerErrorMessageStore.ErrorMessage))
                {
                    OnPropertyChanged(nameof(ServerErrorMessage));
                }
            };

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

        public ICommand BackCmd => new RelayCommand(
            _ => _navigationService.GoBack()
        );


        public bool WindowBackBtn
        {
            get => _navigationService.CanGoBack() && _navigationStore.CurrentViewModel.WindowBackBtn;
        }

        public bool NavBarBackBtn
        {
            get => _navigationService.CanGoBack() && _navigationStore.CurrentViewModel.NavBarBackBtn;
        }



        public ViewModelBase CurrentViewModel => _navigationStore.CurrentViewModel;


        public string ServerErrorMessage => _errorMessageStore.ErrorMessage;

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
            _errorMessageStore.ErrorMessage = "Unable to connect to Server. Trying...";
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
            _errorMessageStore.ErrorType = "";
            _errorMessageStore.ErrorMessage = "";

            _navigationService.NavigateTo<LoginViewModel>();
        }

        internal void OnWindowClosed()
        {
            _socketService.CloseConnection();
        }
    }
}
