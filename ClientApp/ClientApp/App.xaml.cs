using ClientApp.Services;
using ClientApp.ViewModels;
using System.Windows;
using ClientApp.Views.Pages;
using Microsoft.Extensions.DependencyInjection;
using ClientApp.Views.States;
using ClientApp.ViewModels.ForgotPassword;

namespace ClientApp;

/// <summary>
/// Interaction logic for App.xaml
/// </summary>
public partial class App : Application
{
    private IServiceProvider? _serviceProvider;

    protected override void OnStartup(StartupEventArgs e)
    {
        base.OnStartup(e);

        // Configure services
        var services = new ServiceCollection();
        ConfigureServices(services);

        _serviceProvider = services.BuildServiceProvider();

        // Set the main window
        var mainWindow = _serviceProvider.GetService<MainWindow>();
        mainWindow.DataContext = _serviceProvider.GetService<MainWindowViewModel>();
        mainWindow.Show();
    }

    private void ConfigureServices(IServiceCollection services)
    {
        // Register services
        services.AddSingleton<INavigationService, NavigationService>();

        // Register ViewModels
        services.AddTransient<LoginViewModel>();
        services.AddTransient<SignupViewModel>();
        services.AddTransient<MenuViewModel>();
        //   Password reset ViewModels
        services.AddTransient<EmailEntryViewModel>();
        services.AddTransient<CodeEntryViewModel>();
        services.AddTransient<ResetPasswordViewModel>();

        // Register Views
        services.AddTransient<LoginPage>();
        services.AddTransient<SignupPage>();
        services.AddTransient<MenuPage>();

        // Register state
        services.AddSingleton<UserState>();
        services.AddSingleton<PasswordResetState>();



        // Register MainWindow
        services.AddTransient<MainWindow>();
    }

}

