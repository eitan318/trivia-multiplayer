using System.Globalization;
using System.Windows.Data;

namespace ClientApp.Views.Converters
{
    public class EyeIconConverter : IValueConverter
    {
        /// <summary>
        /// Converts a boolean value to an eye icon string.
        /// </summary>
        /// <param name="value">The value to convert. Expected to be a boolean.</param>
        /// <param name="targetType">The target type of the binding. Not used in this converter.</param>
        /// <param name="parameter">Optional parameter. Not used in this converter.</param>
        /// <param name="culture">The culture information for the conversion. Not used in this converter.</param>
        /// <returns>
        /// Returns "Eye" if the boolean value is <c>true</c>, "EyeOff" if <c>false</c>.
        /// If the value is not a boolean, returns "Eye" as the default.
        /// </returns>
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (value is bool isChecked)
            {
                return isChecked ? "EyeOff" : "Eye"; // Eye or EyeOff based on state
            }
            return "Eye";
        }
            
        /// <summary>
        /// not implemented
        /// </summary>
        /// <param name="value"></param>
        /// <param name="targetType"></param>
        /// <param name="parameter"></param>
        /// <param name="culture"></param>
        /// <returns></returns>
        /// <exception cref="NotImplementedException"></exception>
        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }

}
