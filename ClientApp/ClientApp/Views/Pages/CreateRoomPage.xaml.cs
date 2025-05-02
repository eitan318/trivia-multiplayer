using ClientApp.ViewModels;
using System.Windows;
using System.Windows.Controls;

namespace ClientApp.Views.Pages
{
    /// <summary>
    /// Interaction logic for CreateRoomPage.xaml
    /// </summary>
    public partial class CreateRoomPage : NavigablePage
    {
        public CreateRoomPage(Page parent, string user) : base(parent)
        {
            InitializeComponent();
            RoomName_TB.Focus(); // Corrected syntax for Focus
            DataContext = CreateRoomPageViewModel.Instance(user);
        }
    }
}
