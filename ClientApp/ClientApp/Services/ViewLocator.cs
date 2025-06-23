using ClientApp.ViewModels.ForgotPassword;
using ClientApp.ViewModels;
using ClientApp.Views.Screens.ForgotPassword;
using ClientApp.Views.Screens;
using System;
using System.Collections.Generic;
using System.Windows;

namespace ClientApp.Services
{
    public class ViewLocator
    {
        private readonly IServiceProvider _serviceProvider;
        private readonly Dictionary<Type, Type> _viewModelViewMap = new();

        public ViewLocator(IServiceProvider serviceProvider)
        {
            _serviceProvider = serviceProvider;

            // Register mappings
            RegisterMappings();
        }

        private void RegisterMappings()
        {
            _viewModelViewMap[typeof(MainWindowViewModel)] = typeof(MainWindow);

            _viewModelViewMap[typeof(LoginViewModel)] = typeof(LoginView);
            _viewModelViewMap[typeof(SignupViewModel)] = typeof(SignupView);
            _viewModelViewMap[typeof(MenuViewModel)] = typeof(MenuView);
            _viewModelViewMap[typeof(RoomMemberViewModel)] = typeof(RoomMemberView);
            _viewModelViewMap[typeof(RoomAdminViewModel)] = typeof(RoomAdminView);
            _viewModelViewMap[typeof(StatisticsViewModel)] = typeof(StatisticsView);
            _viewModelViewMap[typeof(HighScoresViewModel)] = typeof(HighScoresView);
            _viewModelViewMap[typeof(PersonalStatisticsViewModel)] = typeof(PersonalStatisticsView);
            _viewModelViewMap[typeof(CreateRoomViewModel)] = typeof(CreateRoomView);
            _viewModelViewMap[typeof(JoinRoomViewModel)] = typeof(JoinRoomView);
            _viewModelViewMap[typeof(ErrorViewModel)] = typeof(ErrorView);
            _viewModelViewMap[typeof(GameAnsweringViewModel)] = typeof(GameAnsweringView);
            _viewModelViewMap[typeof(GameResultsViewModel)] = typeof(GameResultsView);
            _viewModelViewMap[typeof(WaitingBetweenQuestionsViewModel)] = typeof(WaitingBetweenQuestionsView);
            _viewModelViewMap[typeof(GameScoreBoardViewModel)] = typeof(GameScoreBoardView);
            _viewModelViewMap[typeof(Waiting1v1ViewModel)] = typeof(Waiting1v1View);

            // Password reset mappings
            _viewModelViewMap[typeof(EmailEntryViewModel)] = typeof(EmailEntryView);
            _viewModelViewMap[typeof(CodeEntryViewModel)] = typeof(CodeEntryView);
            _viewModelViewMap[typeof(ResetPasswordViewModel)] = typeof(ResetPasswordView);
        }

        public FrameworkElement GetView(object viewModel)
        {
            if (viewModel == null) throw new ArgumentNullException(nameof(viewModel));

            var viewModelType = viewModel.GetType();
            if (!_viewModelViewMap.TryGetValue(viewModelType, out var viewType))
            {
                throw new InvalidOperationException($"No view was mapped to {viewModelType.FullName}.");
            
            }

            var view = _serviceProvider.GetService(viewType) as FrameworkElement;

            if (view == null)
            {
                throw new InvalidOperationException($"The view {viewType.FullName} could not be resolved.");
            }

            // Set the DataContext of the view to the ViewModel
            view.DataContext = viewModel;
            return view;
        }
    }
}

