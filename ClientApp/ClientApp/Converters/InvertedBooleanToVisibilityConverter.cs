using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;
using System.Windows;

namespace ClientApp.Converters
{
    public class InvertedBooleanToVisibilityConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            // Check if the value is boolean and return inverted Visibility
            if (value is bool booleanValue)
            {
                return booleanValue ? Visibility.Collapsed : Visibility.Visible;
            }
            return Visibility.Visible; // Default to Visible if the value isn't boolean
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            // This converter does not support ConvertBack.
            throw new NotImplementedException();
        }
    }
}
