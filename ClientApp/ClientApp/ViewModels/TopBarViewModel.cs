using ClientApp.Commands;
using ClientApp.Services;
using ClientApp.Stores;
using System.ComponentModel;
using System.Windows.Input;

namespace ClientApp.ViewModels
{
    public class TopBarViewModel : ViewModelBase
    {
        private readonly NavigationStore _navigationStore;
        private readonly UserStore _userStore;

        public string TopBarUsername => _userStore.Username;

        public ICommand LogoutCmd { get; }

        public ICommand BackCmd { get; }

        public bool ShowBackButton => _navigationStore.CurrentViewModel?.NavBarBackBtn ?? false;

        public TopBarViewModel(LogoutCommand logoutCmd, 
            UserStore userStore, 
            NavigationStore navigationStore,
            INavigationService navigationService)
        {
            _navigationStore = navigationStore;
            _userStore = userStore;

            LogoutCmd = logoutCmd;
            BackCmd = new RelayCommand(_ => navigationService.GoBack());

            _navigationStore.PropertyChanged += NavigationStore_PropertyChanged;
            _userStore.PropertyChanged += UserStore_PropertyChanged;
        }

        private void NavigationStore_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            if (e.PropertyName == nameof(NavigationStore.CurrentViewModel))
            {
                OnPropertyChanged(nameof(ShowBackButton));
            }
        }

        private void UserStore_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            if (e.PropertyName == nameof(UserStore.Username))
            {
                OnPropertyChanged(nameof(TopBarUsername));
            }
        }
    }
}
