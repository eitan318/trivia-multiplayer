using System.Configuration;
using System.Data;
using System.Windows;

namespace ClientApp;

/// <summary>
/// Interaction logic for App.xaml
/// </summary>
public partial class App : Application
{
    private void App_Shutdown(object sender, EventArgs e)
    {
        // Perform cleanup for the entire application
        Console.WriteLine("Application is shutting down...");
    }

}

