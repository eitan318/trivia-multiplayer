using ClientApp.Services;
using ClientApp.ViewModels;
using System.Windows;
using ClientApp.Views.Pages;
using ClientApp.Views.Pages.ForgotPassword;
using Microsoft.Extensions.DependencyInjection;
using ClientApp.ViewModels.ForgotPassword;
using ClientApp.Stores;

namespace ClientApp;

/// <summary>
/// Interaction logic for App.xaml
/// </summary>
public partial class App : Application
{
    private readonly IServiceProvider? _serviceProvider;

    public App()
    {
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


        // Register ViewModels
        services.AddTransient<MainWindowViewModel>();

        services.AddTransient<LoginViewModel>(s => CreateLoginViewModel(s));
        services.AddTransient<SignupViewModel>();
        services.AddTransient<MenuViewModel>();
        services.AddTransient<MemberRoomViewModel>();
        services.AddTransient<AdminRoomViewModel>();
        services.AddTransient<StatisticsViewModel>();
        services.AddTransient<HighScoresViewModel>();
        services.AddTransient<PersonalStatisticsViewModel>();
        services.AddTransient<CreateRoomViewModel>();
        services.AddTransient<JoinRoomViewModel>();
        services.AddTransient<ErrorViewModel>();

        //   Password reset ViewModels
        services.AddTransient<EmailEntryViewModel>();
        services.AddTransient<CodeEntryViewModel>();
        services.AddTransient<ResetPasswordViewModel>();

        // Register Views
        services.AddTransient<LoginView>();
        services.AddTransient<SignupView>();
        services.AddTransient<MenuView>();
        services.AddTransient<MemberRoomView>();
        services.AddTransient<AdminRoomView>();
        services.AddTransient<StatisticsView>();
        services.AddTransient<HighScoresView>();
        services.AddTransient<PersonalStatisticsView>();
        services.AddTransient<CreateRoomView>();
        services.AddTransient<JoinRoomView>();
        services.AddTransient<ErrorView>();

        // Password reset Views
        services.AddTransient<EmailEntryView>();
        services.AddTransient<CodeEntryView>();
        services.AddTransient<ResetPasswordView>();

        // Register stores
        services.AddSingleton<UserStore>();
        services.AddSingleton<PasswordResetStore>();
        services.AddSingleton<ErrorMessageStore>();
        services.AddSingleton<NavigationStore>();
        services.AddSingleton<RoomDataStore>();

        // Register MainWindow
        services.AddTransient<MainWindow>(sp =>
        {
            var viewModel = sp.GetRequiredService<MainWindowViewModel>();
            return new MainWindow(viewModel);
        });

    }


    private LoginViewModel CreateLoginViewModel(IServiceProvider serviceProvider)
    {
        return new LoginViewModel(
            serviceProvider.GetRequiredService<INavigationService>(),
            serviceProvider.GetRequiredService<UserStore>(),
            serviceProvider.GetRequiredService<RequestsExchangeService>()

            );
    }

}

