using System.Globalization;
using System.Windows.Data;
using System.Windows;

namespace ClientApp.Views.Converters
{
    /// <summary>
    /// Converts a string value to a <see cref="Visibility"/> value.
    /// </summary>
    public class StringToVisibilityConverter : IValueConverter
    {
        /// <summary>
        /// Converts a string value to <see cref="Visibility.Visible"/> if the string is not null or whitespace; 
        /// otherwise, converts it to <see cref="Visibility.Collapsed"/>.
        /// </summary>
        /// <param name="value">The string value to convert.</param>
        /// <param name="targetType">The target type of the conversion, which is expected to be <see cref="Visibility"/>.</param>
        /// <param name="parameter">Optional parameter. Not used in this converter.</param>
        /// <param name="culture">The culture information for the conversion. Not used in this converter.</param>
        /// <returns>
        /// <see cref="Visibility.Visible"/> if the string is not null or whitespace; 
        /// <see cref="Visibility.Collapsed"/> if the string is null, empty, or consists only of whitespace.
        /// </returns>
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (value is string str && !string.IsNullOrWhiteSpace(str))
            {
                return Visibility.Visible;
            }
            return Visibility.Collapsed;
        }

        /// <summary>
        /// This converter does not support converting back from <see cref="Visibility"/> to string.
        /// </summary>
        /// <param name="value">The value to convert back. Not used in this converter.</param>
        /// <param name="targetType">The target type of the binding. Not used in this converter.</param>
        /// <param name="parameter">Optional parameter. Not used in this converter.</param>
        /// <param name="culture">The culture information for the conversion. Not used in this converter.</param>
        /// <returns>Always throws a <see cref="NotImplementedException"/>.</returns>
        /// <exception cref="NotImplementedException">Thrown as this method is not implemented.</exception>
        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException("ConvertBack is not supported for StringToVisibilityConverter.");
        }
    }
}
