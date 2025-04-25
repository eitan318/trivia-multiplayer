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
    /// <summary>
    /// Converts a boolean value to the inverse of the corresponding <see cref="Visibility"/> value.
    /// </summary>
    public class InvertedBooleanToVisibilityConverter : IValueConverter
    {
        /// <summary>
        /// Converts a boolean value to its inverse <see cref="Visibility"/> representation.
        /// </summary>
        /// <param name="value">The boolean value to convert.</param>
        /// <param name="targetType">The target type of the conversion, which is expected to be <see cref="Visibility"/>.</param>
        /// <param name="parameter">Optional parameter. Not used in this converter.</param>
        /// <param name="culture">The culture information for the conversion. Not used in this converter.</param>
        /// <returns>
        /// <see cref="Visibility.Collapsed"/> if the boolean value is <c>true</c>, 
        /// <see cref="Visibility.Visible"/> if the boolean value is <c>false</c>.
        /// If the value is not a boolean, defaults to <see cref="Visibility.Visible"/>.
        /// </returns>
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            // Check if the value is boolean and return inverted Visibility
            if (value is bool booleanValue)
            {
                return booleanValue ? Visibility.Collapsed : Visibility.Visible;
            }
            return Visibility.Visible; // Default to Visible if the value isn't boolean
        }

        /// <summary>
        /// This converter does not support converting back from <see cref="Visibility"/> to boolean.
        /// </summary>
        /// <param name="value">The value to convert back. Not used in this converter.</param>
        /// <param name="targetType">The target type of the binding. Not used in this converter.</param>
        /// <param name="parameter">Optional parameter. Not used in this converter.</param>
        /// <param name="culture">The culture information for the conversion. Not used in this converter.</param>
        /// <returns>Always throws a <see cref="NotImplementedException"/>.</returns>
        /// <exception cref="NotImplementedException">Thrown as this method is not implemented.</exception>
        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            // This converter does not support ConvertBack.
            throw new NotImplementedException();
        }
    }
}
