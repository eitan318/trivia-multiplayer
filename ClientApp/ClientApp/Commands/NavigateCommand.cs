using ClientApp.Services;
using ClientApp.ViewModels;
using System.Windows.Input;

namespace ClientApp.Commands
{
    public class NavigateCommand<TViewModel> : ICommand where TViewModel : ViewModelBase
    {
        private readonly INavigationService _navigationService;

        public NavigateCommand(INavigationService navigationService)
        {
            _navigationService = navigationService ?? throw new ArgumentNullException(nameof(navigationService));
        }

        public event EventHandler? CanExecuteChanged;

        public bool CanExecute(object? parameter)
        {
            // Optionally add logic to enable/disable the command
            return true;
        }

        public void Execute(object? parameter)
        {
            _navigationService.NavigateTo<TViewModel>();
        }
    }
}

