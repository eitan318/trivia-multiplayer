using System.Windows;
using System.Windows.Controls;

namespace ClientApp.Views.Pages
{
    public class CustomPage : Page
    {
        public static readonly DependencyProperty ShowBackButtonProperty =
            DependencyProperty.Register("ShowBackButton", typeof(bool), typeof(CustomPage), new PropertyMetadata(true));

        public bool ShowBackButton
        {
            get => (bool)GetValue(ShowBackButtonProperty);
            set => SetValue(ShowBackButtonProperty, value);
        }
    }

}
