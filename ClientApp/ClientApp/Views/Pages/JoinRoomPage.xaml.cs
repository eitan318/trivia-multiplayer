using System.Windows.Controls;

namespace ClientApp.Views.Pages
{
    /// <summary>
    /// Interaction logic for JoinRoomPage.xaml
    /// </summary>
    public partial class JoinRoomPage : CustomPage
    {
        public JoinRoomPage(string user) 
        {
            InitializeComponent();
            DataContext = JoinRoomViewModel.Instance(this, user);
            
        }
    }
}
