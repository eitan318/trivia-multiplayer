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
        private readonly Dictionary<Type, ScreenViewModelBase> _viewModelCache = new(); // ViewModel caching

        public NavigationService(IServiceProvider serviceProvider, NavigationStore navigationStore)
        {
            _serviceProvider = serviceProvider;
            _navigationStore = navigationStore;
        }

        public void NavigateTo<TViewModel>() where TViewModel : ScreenViewModelBase
        {
            var type = typeof(TViewModel);

            // Check if the ViewModel is already in the cache
            if (!_viewModelCache.TryGetValue(type, out var viewModel))
            {
                // Resolve ViewModel via service provider and cache it
                viewModel = _serviceProvider.GetService(type) as TViewModel;
                if (viewModel == null)
                    throw new InvalidOperationException($"Service for {type.Name} could not be resolved.");

                _viewModelCache[type] = viewModel;
            }

            // Set the current ViewModel
            _navigationStore.CurrentViewModel = viewModel;
        }


        public void GoBack()
        {
            if(_navigationStore.CanGoBack())
            {
                 _navigationStore.GoBack();
            }
            
        }

        // Optional: Add a method to clear or remove ViewModels from the cache
        public void ClearViewModelCache()
        {
            _viewModelCache.Clear();
        }

        public void RemoveViewModelFromCache<TViewModel>() where TViewModel : ViewModelBase
        {
            _viewModelCache.Remove(typeof(TViewModel));
        }
    }
}
