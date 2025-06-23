using ClientApp.Stores;
using ClientApp.ViewModels;
using Microsoft.Extensions.DependencyInjection;
using System;
using System.Collections.Generic;
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

        public void NavigateTo<TViewModel>() where TViewModel : ScreenViewModelBase
        {
            var viewModel = _serviceProvider.GetService<TViewModel>();

            if (viewModel == null)
            {
                throw new InvalidOperationException($"ViewModel of type {typeof(TViewModel).FullName} could not be resolved.");
            }
            _navigationStore.CurrentViewModel = viewModel;
            ChangeView(viewModel);

        }


        public void GoBack()
        {
            if(CanGoBack())
            {
                _navigationStore.GoBack();
                ChangeView(_navigationStore.CurrentViewModel);
            }
            
        }
        public bool CanGoBack()
        {
            return _navigationStore.CanGoBack();
        }

        private void ChangeView(ScreenViewModelBase viewModel)
        {
            var viewLocator = _serviceProvider.GetService<ViewLocator>();
            var view = viewLocator.GetView(viewModel);

            var mainWindow = Application.Current.MainWindow;
            if (mainWindow is MainWindow window)
            {
                window.MainContentFrame.Content = view;
            }
        }
    }
}
