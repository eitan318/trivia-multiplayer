using ClientApp.ViewModels;
using System.Windows.Controls;

namespace ClientApp.Views.Pages
{
    /// <summary>
    /// Interaction logic for CreateRoomPage.xaml
    /// </summary>
    public partial class CreateRoomPage : CustomPage
    {
        public CreateRoomPage(string user) 
        {
            InitializeComponent();
            RoomName_TB.Focus(); // Corrected syntax for Focus
            DataContext = CreateRoomViewModel.Instance(user);
        }
    }
}
