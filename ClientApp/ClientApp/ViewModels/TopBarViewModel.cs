using ClientApp.Commands;
using ClientApp.Services;
using ClientApp.Stores;
using System.Windows.Input;

namespace ClientApp.ViewModels
{
    public class TopBarViewModel : ViewModelBase
    {
        private readonly INavigationService _navigationService;
        private readonly NavigationStore _navigationStore;
        private readonly UserStore _userStore;

        public string TopBarUsername => _userStore.Username;

        public ICommand LogoutCmd { get; }

        public ICommand BackCmd => new RelayCommand(
            _ => _navigationService.GoBack()
        );

        public bool ShowBackButton => _navigationStore.CurrentViewModel.NavBarBackBtn;

        public TopBarViewModel(LogoutCommand logoutCmd,
            UserStore userStore,
            INavigationService navigationService,
            NavigationStore navigationStore)
        {
            this._navigationService = navigationService;
            _navigationStore = navigationStore;
            LogoutCmd = logoutCmd;
            _userStore = userStore;

            // Subscribe to changes in the UserStore
            _userStore.PropertyChanged += (s, e) =>
            {
                if (e.PropertyName == nameof(UserStore.Username))
                {
                    OnPropertyChanged(nameof(TopBarUsername)); // Notify that Username has changed
                }
            };
        }
    }
}
