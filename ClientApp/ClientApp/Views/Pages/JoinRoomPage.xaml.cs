using System.Windows.Controls;

namespace ClientApp.Views.Pages
{
    /// <summary>
    /// Interaction logic for JoinRoomPage.xaml
    /// </summary>
    public partial class JoinRoomPage : NavigablePage
    {
        public JoinRoomPage(Page parent, string user) : base(parent)
        {
            InitializeComponent();
            DataContext = JoinRoomViewModel.Instance(this, user);
            
        }
    }
}
