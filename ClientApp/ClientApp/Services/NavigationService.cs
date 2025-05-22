using ClientApp.ViewModels;

namespace ClientApp.Services
{
    public class NavigationService : INavigationService
    {
        private readonly IServiceProvider _serviceProvider;

        public NavigationService(IServiceProvider serviceProvider)
        {
            _serviceProvider = serviceProvider;
        }

        public void NavigateTo<TViewModel>() where TViewModel : ViewModelBase
        {
            var viewModel = _serviceProvider.GetService(typeof(TViewModel)) as TViewModel;

            if (viewModel == null)
                throw new InvalidOperationException($"Service for {typeof(TViewModel).Name} could not be resolved.");

            var viewType = Type.GetType(viewModel.GetType().Name.Replace("ViewModel", "View"));
            if (viewType == null)
                throw new InvalidOperationException($"View type for {viewModel.GetType().Name} could not be resolved.");

            var view = _serviceProvider.GetService(viewType);
            if (view == null)
                throw new InvalidOperationException($"Service for {viewType.Name} could not be resolved.");

            App.Current.MainWindow.Content = view;
        }

        public void GoBack()
        {
            // Implement back navigation logic
        }
    }
}
