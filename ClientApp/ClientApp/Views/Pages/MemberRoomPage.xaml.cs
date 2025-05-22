using ClientApp.Models;
using ClientApp.ViewModels;
using System.Windows.Controls;
namespace ClientApp.Views.Pages
{
    /// <summary>
    /// Interaction logic for RoomPage.xaml
    /// </summary>
    partial class MemberRoomPage : Page
    {
        public MemberRoomPage(RoomData roomData, string user)
        {
            InitializeComponent();
            DataContext = MemberRoomViewModel.Instance(roomData, user);
        }
    }
}
