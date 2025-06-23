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
using System.Windows.Shapes;
using static MaterialDesignThemes.Wpf.Theme;

namespace ClientApp
{
    /// <summary>
    /// Interaction logic for IPInputDialog.xaml
    /// </summary>
    public partial class IPInputDialog : Window
    {
        public string? IpAddress { get; private set; }

        public IPInputDialog()
        {
            InitializeComponent();
        }

        private void OnOkClick(object sender, RoutedEventArgs e)
        {
            IpAddress = IpTextBox.Text;
            DialogResult = true; // Close the dialog and indicate success
            Close();
        }
    }
}
