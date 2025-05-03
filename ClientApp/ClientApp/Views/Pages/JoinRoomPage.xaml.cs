using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using ClientApp.ViewModels;

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
