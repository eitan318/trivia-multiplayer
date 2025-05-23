using ClientApp.Stores;
using ClientApp.ViewModels;
using System;
using System.Windows;

namespace ClientApp.Services
{
    class NavigationService : INavigationService
    {
        private readonly IServiceProvider _serviceProvider;
        private readonly NavigationStore _navigationStore;

        public NavigationService(IServiceProvider serviceProvider, NavigationStore navigationStore)
        {
            _serviceProvider = serviceProvider;
            _navigationStore = navigationStore;
        }

        public void NavigateTo<TViewModel>() where TViewModel : ViewModelBase
        {
            var viewModel = _serviceProvider.GetService(typeof(TViewModel)) as TViewModel;
            if (viewModel == null)
                throw new InvalidOperationException($"Service for {typeof(TViewModel).Name} could not be resolved.");

            _navigationStore.CurrentViewModel = viewModel;
        }

        public void GoBack()
        {
            if (_navigationStore.CanGoBack())
            {
                _navigationStore.GoBack();
            }
        }
    }
}
