using ClientApp.ViewModels;
using System.Windows.Controls;

namespace ClientApp.Views.Screens
{
    /// <summary>
    /// Interaction logic for CreateRoomPage.xaml
    /// </summary>
    public partial class CreateRoomView : UserControl
    {
        public CreateRoomView() 
        {
            InitializeComponent();
            // Use Loaded event to delay focus
            Loaded += (s, e) => RoomName_TB.Focus();
        }
    }
}
