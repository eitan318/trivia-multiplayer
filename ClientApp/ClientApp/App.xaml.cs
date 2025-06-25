using ClientApp.Services;
using ClientApp.ViewModels;
using System.Windows;
using ClientApp.Views.Screens;
using ClientApp.Views.Screens.ForgotPassword;
using Microsoft.Extensions.DependencyInjection;
using ClientApp.ViewModels.ForgotPassword;
using ClientApp.Stores;
using ClientApp.Views.Controls;
using ClientApp.Commands;
using System.Windows.Input;

namespace ClientApp;

/// <summary>
/// Interaction logic for App.xaml
/// </summary>
public partial class App : Application
{
    private readonly IServiceProvider? _serviceProvider;

    [System.Runtime.InteropServices.DllImport("kernel32.dll")]
    private static extern bool AllocConsole();

    public App()
    {
         //AllocConsole();

        // Configure services
        var services = new ServiceCollection();
        ConfigureServices(services);

        _serviceProvider = services.BuildServiceProvider();
    }
    protected override void OnStartup(StartupEventArgs e)
    {
        base.OnStartup(e);

        var mainWindowViewModel = _serviceProvider.GetRequiredService<MainWindowViewModel>();
        var mainWindow = new MainWindow(mainWindowViewModel);

        Application.Current.MainWindow = mainWindow;
        mainWindowViewModel.Initialize();
        mainWindow.Show();
    }


    private void ConfigureServices(IServiceCollection services)
    {



        // Register ViewModels
        services.AddSingleton<MainWindowViewModel>();
        services.AddSingleton<LoginViewModel>();
        services.AddSingleton<SignupViewModel>();
        services.AddSingleton<MenuViewModel>();
        services.AddSingleton<RoomMemberViewModel>();
        services.AddSingleton<RoomAdminViewModel>();
        services.AddSingleton<StatisticsViewModel>();
        services.AddSingleton<HighScoresViewModel>();
        services.AddSingleton<PersonalStatisticsViewModel>();
        services.AddSingleton<CreateRoomViewModel>();
        services.AddSingleton<JoinRoomViewModel>();
        services.AddSingleton<ErrorViewModel>();
        services.AddSingleton<GameAnsweringViewModel>();
        services.AddSingleton<GameResultsViewModel>();
        services.AddSingleton<WaitingBetweenQuestionsViewModel>();
        services.AddSingleton<GameScoreBoardViewModel>();
        services.AddSingleton<Waiting1v1ViewModel>();
        services.AddSingleton<TopBarViewModel>();
        services.AddSingleton<EmailEntryViewModel>();
        services.AddSingleton<CodeEntryViewModel>();
        services.AddSingleton<ResetPasswordViewModel>();





        // Register services
        services.AddSingleton<INavigationService, NavigationService>();
        services.AddSingleton(sp => new SocketService("127.0.0.1", 5554));
        services.AddSingleton<RequestsExchangeService>();
        services.AddSingleton<JsonRequestSerializer>();
        services.AddSingleton<JsonResponseDeserializer>();
        services.AddSingleton<ViewLocator>();






        // Register commands
        services.AddTransient(typeof(NavigateCommand<>));
        services.AddTransient<LogoutCommand>();
        services.AddTransient<CreateRoomCommand>();
        services.AddTransient<JoinCommand>();
        services.AddTransient<LeaveGameCommand>();
        services.AddTransient<LeaveRoomCommand>();
        services.AddTransient<LoginCommand>();
        services.AddTransient<ResetPasswordCommand>();
        services.AddTransient<SignupCommand>();
        services.AddTransient<StartGameCommand>();
        services.AddTransient<SubmitAnswerCommand>();
        services.AddTransient<SubmitPasswordResetCodeCommand>();
        services.AddTransient<SubmitPasswordResetEmailCommand>();
        services.AddTransient<Join1v1WaitingListCommand>();
        services.AddTransient<LeaveWaitingListCommand>();



        // Register Views
        services.AddTransient<LoginView>();
        services.AddTransient<SignupView>();
        services.AddTransient<MenuView>();
        services.AddTransient<RoomMemberView>();
        services.AddTransient<RoomAdminView>();
        services.AddTransient<StatisticsView>();
        services.AddTransient<HighScoresView>();
        services.AddTransient<PersonalStatisticsView>();
        services.AddTransient<CreateRoomView>();
        services.AddTransient<JoinRoomView>();
        services.AddTransient<ErrorView>();
        services.AddTransient<GameAnsweringView>();
        services.AddTransient<GameResultsView>();
        services.AddTransient<WaitingBetweenQuestionsView>();
        services.AddTransient<GameScoreBoardView>();
        services.AddTransient<EmailEntryView>();
        services.AddTransient<CodeEntryView>();
        services.AddTransient<ResetPasswordView>();
        services.AddTransient<Waiting1v1View>();





        // Register stores
        services.AddSingleton<UserStore>();
        services.AddSingleton<PasswordResetStore>();
        services.AddSingleton<ServerErrorMessageStore>();
        services.AddSingleton<NavigationStore>();
        services.AddSingleton<RoomDataStore>();
        services.AddSingleton<AmIAdminStore>();


        // Register MainWindow
        services.AddTransient<MainWindow>(sp =>
        {
            var viewModel = sp.GetRequiredService<MainWindowViewModel>();
            return new MainWindow(viewModel);
        });
    }
    protected override void OnExit(ExitEventArgs e)
    {
        base.OnExit(e);

        DisposeViewModels();
    }

    private void DisposeViewModels()
    {
        if (_serviceProvider == null) return;

        using (var scope = _serviceProvider.CreateScope())
        {
            foreach (var service in _serviceProvider.GetServices<object>())
            {
                if (service is IDisposable disposable)
                {
                    disposable.Dispose();
                }
            }
        }
    }

}

