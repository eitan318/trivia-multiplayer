using ClientApp.ViewModels;
using System.Windows.Controls;

namespace ClientApp.Views.Pages
{
    /// <summary>
    /// Interaction logic for CreateRoomPage.xaml
    /// </summary>
    public partial class CreateRoomView : CustomUserControl
    {
        public CreateRoomView() 
        {
            InitializeComponent();
            RoomName_TB.Focus(); 
        }
    }
}
