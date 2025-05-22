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

            var viewTypeName = $"{typeof(TViewModel).Namespace?.Replace("ViewModels", "Views.Pages")}.{typeof(TViewModel).Name.Replace("ViewModel", "View")}";
            var viewType = Type.GetType(viewTypeName);

            if (viewType == null)
                throw new InvalidOperationException($"View type for {typeof(TViewModel).Name} could not be resolved.");

            var view = _serviceProvider.GetService(viewType) as FrameworkElement;
            if (view == null)
                throw new InvalidOperationException($"Service for {viewType.Name} could not be resolved.");

            view.DataContext = viewModel;
            _navigationStore.CurrentView = view;
        }

        public void GoBack()
        {
            // Implement back navigation logic
        }
    }
}
