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
        // Set the main window
        var mainWindow = _serviceProvider.GetService<MainWindow>();
        mainWindow.Show();
        base.OnStartup(e);
    }

    private void ConfigureServices(IServiceCollection services)
    {
        // Register services
        services.AddSingleton<INavigationService, NavigationService>();
        services.AddSingleton(sp => new SocketService("127.0.0.1", 5554));
        services.AddSingleton<RequestsExchangeService>();
        services.AddSingleton<JsonRequestSerializer>();
        services.AddSingleton<JsonResponseDeserializer>();






        // Register ViewModels
        services.AddTransient<MainWindowViewModel>();

        services.AddTransient<LoginViewModel>();
        services.AddTransient<SignupViewModel>();
        services.AddTransient<MenuViewModel>();
        services.AddTransient<RoomMemberViewModel>();
        services.AddTransient<RoomAdminViewModel>();
        services.AddTransient<StatisticsViewModel>();
        services.AddTransient<HighScoresViewModel>();
        services.AddTransient<PersonalStatisticsViewModel>();
        services.AddTransient<CreateRoomViewModel>();
        services.AddTransient<JoinRoomViewModel>();
        services.AddTransient<ErrorViewModel>();
        services.AddTransient<GameAnsweringViewModel>();
        services.AddTransient<GameResultsViewModel>();
        services.AddTransient<WaitingBetweenQuestionsViewModel>();
        services.AddTransient<GameScoreBoardViewModel>();
        services.AddTransient<Waiting1v1ViewModel>();


        services.AddTransient<TopBarViewModel>();

        

        // Password reset ViewModels
        services.AddTransient<EmailEntryViewModel>();
        services.AddTransient<CodeEntryViewModel>();
        services.AddTransient<ResetPasswordViewModel>();




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

        // Password reset Views
        services.AddTransient<EmailEntryView>();
        services.AddTransient<CodeEntryView>();
        services.AddTransient<ResetPasswordView>();

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
}

