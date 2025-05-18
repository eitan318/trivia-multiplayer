using System.Globalization;
using System.Windows.Data;
using System.Windows.Media;

namespace ClientApp.Views.Converters
{
    public class BoolToBorderBrushConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            // Check if the value is a boolean
            if (value is bool isMe)
            {
                // Return the appropriate brush based on the boolean value
                //return isMe ? Brushes.Transparent :
                //    (Brush)System.Windows.Application.Current.Resources["PrimaryColor"];
                return isMe ? Brushes.Aqua : Brushes.Transparent;
            }

            // Default to Red if the value is not a boolean (you can adjust this logic)
            return Brushes.Red;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            // Not used in this case
            return null;
        }
    }
}
