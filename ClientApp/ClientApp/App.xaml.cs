using ClientApp.Services;
using ClientApp.ViewModels;
using System.Windows;
using ClientApp.Views.Pages;
using Microsoft.Extensions.DependencyInjection;
using ClientApp.ViewModels.ForgotPassword;
using ClientApp.Stores;

namespace ClientApp;

/// <summary>
/// Interaction logic for App.xaml
/// </summary>
public partial class App : Application
{
    private IServiceProvider? _serviceProvider;

    protected override void OnStartup(StartupEventArgs e)
    {
        // Configure services
        var services = new ServiceCollection();
        ConfigureServices(services);

        _serviceProvider = services.BuildServiceProvider();

        // Set the main window
        var mainWindow = _serviceProvider.GetService<MainWindow>();
        mainWindow.DataContext = _serviceProvider.GetService<MainWindowViewModel>();
        mainWindow.Show();
        base.OnStartup(e);
    }

    private void ConfigureServices(IServiceCollection services)
    {
        // Register services
        services.AddSingleton<INavigationService, NavigationService>();

        // Register ViewModels
        services.AddTransient<MainWindowViewModel>();

        services.AddTransient<LoginViewModel>();
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

        // Register stores
        services.AddSingleton<UserStore>();
        services.AddSingleton<PasswordResetStore>();
        services.AddSingleton<ErrorMessageStore>();
        services.AddSingleton<NavigationStore>();

        // Register MainWindow
        services.AddTransient<MainWindow>();
    }

}

