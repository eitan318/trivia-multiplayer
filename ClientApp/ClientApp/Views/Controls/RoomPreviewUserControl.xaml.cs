using System.Windows;
using System.Windows.Controls;
namespace ClientApp.Views.Controls
{
    /// <summary>
    /// Interaction logic for RoomDataUserControl.xaml
    /// </summary>
    public partial class RoomPreviewUserControl : UserControl
    {
        public RoomPreviewUserControl()
        {
            InitializeComponent();
        }
        public static readonly DependencyProperty SearchQueryProperty =
            DependencyProperty.Register(
                nameof(SearchQuery),
                typeof(string),
                typeof(RoomPreviewUserControl),
                new PropertyMetadata(string.Empty));

        public string SearchQuery
        {
            get => (string)GetValue(SearchQueryProperty);
            set => SetValue(SearchQueryProperty, value);
        }

    }
}
