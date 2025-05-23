using ClientApp.Commands;
using ClientApp.Services;
using ClientApp.Stores;
using Microsoft.Xaml.Behaviors.Core;
using System;
using System.Threading.Tasks;
using System.Windows.Input;
using System.Windows.Navigation;

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

            _navigationStore.CurrentViewModelChanged += OnCurrentViewModelChanged;
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

        public ICommand BackCmd => new RelayCommand(
            _ => _navigationStore.GoBack()
        );


        public bool CanGoBack
        {
            get => _navigationStore.CanGoBack() && _navigationStore.CurrentViewModel.HasBackBtn;
        }

        
        public ViewModelBase CurrentViewModel => _navigationStore.CurrentViewModel;




        private void OnCurrentViewModelChanged()
        {
            OnPropertyChanged(nameof(CurrentViewModel));
            OnPropertyChanged(nameof(CanGoBack));
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
