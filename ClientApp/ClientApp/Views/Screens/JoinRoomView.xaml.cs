using System.Windows.Controls;

namespace ClientApp.Views.Screens
{
    /// <summary>
    /// Interaction logic for JoinRoomPage.xaml
    /// </summary>
    public partial class JoinRoomView : UserControl
    {
        public JoinRoomView() 
        {
            InitializeComponent();
            Search_TBX.Focus();
        }
    }
}
