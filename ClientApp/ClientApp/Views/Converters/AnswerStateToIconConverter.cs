using System;
using System.Globalization;
using System.Windows.Data;
using ClientApp.Enums;

namespace ClientApp.Views.Converters
{
    public class AnswerStateToIconConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (value is AnswerState state)
            {
                return state switch
                {
                    AnswerState.Correct => "CheckCircle",
                    AnswerState.Wrong => "remove",
                    AnswerState.NoAnswer => "", // '-' icon
                    _ => throw new ArgumentOutOfRangeException()
                };
            }

            return null; // Or a default icon
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
