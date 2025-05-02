using ClientApp.Models;
using ClientApp.ViewModels;
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
            DataContext = MemberRoomPageViewModel.Instance(roomData, user);
        }
    }
}
