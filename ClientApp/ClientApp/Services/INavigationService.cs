using ClientApp.ViewModels;

namespace ClientApp.Services
{
    public interface INavigationService
    {
        void NavigateTo<TViewModel>() where TViewModel : ScreenViewModelBase;
        void GoBack();
        bool CanGoBack();
    }
}
