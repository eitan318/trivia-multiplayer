using System.Windows;
using System.Windows.Controls;

namespace ClientApp.Controls
{
    public partial class PasswordBoxWithToggle : UserControl
    {
        public PasswordBoxWithToggle()
        {
            InitializeComponent();
        }

        // Dependency Property for PasswordBox Style
        public static readonly DependencyProperty InnerPasswordBoxStyleProperty =
            DependencyProperty.Register(
                nameof(InnerPasswordBoxStyle),
                typeof(Style),
                typeof(PasswordBoxWithToggle),
                new PropertyMetadata(null, OnInnerPasswordBoxStyleChanged));

        public Style InnerPasswordBoxStyle
        {
            get => (Style)GetValue(InnerPasswordBoxStyleProperty);
            set => SetValue(InnerPasswordBoxStyleProperty, value);
        }

        private static void OnInnerPasswordBoxStyleChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            if (d is PasswordBoxWithToggle control && e.NewValue is Style newStyle)
            {
                control.PasswordBox.Style = newStyle;
            }
        }

        // Dependency Property for TextBox Style
        public static readonly DependencyProperty InnerTextBoxStyleProperty =
            DependencyProperty.Register(
                nameof(InnerTextBoxStyle),
                typeof(Style),
                typeof(PasswordBoxWithToggle),
                new PropertyMetadata(null, OnInnerTextBoxStyleChanged));

        public Style InnerTextBoxStyle
        {
            get => (Style)GetValue(InnerTextBoxStyleProperty);
            set => SetValue(InnerTextBoxStyleProperty, value);
        }

        private static void OnInnerTextBoxStyleChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            if (d is PasswordBoxWithToggle control && e.NewValue is Style newStyle)
            {
                control.VisiblePasswordBox.Style = newStyle;
            }
        }

        // Define IsPasswordVisible as a DependencyProperty
        public static readonly DependencyProperty IsPasswordVisibleProperty =
            DependencyProperty.Register(nameof(IsPasswordVisible), typeof(bool), typeof(PasswordBoxWithToggle), new PropertyMetadata(false));

        public bool IsPasswordVisible
        {
            get => (bool)GetValue(IsPasswordVisibleProperty);
            set => SetValue(IsPasswordVisibleProperty, value);
        }

        // Define PasswordText as a DependencyProperty
        public static readonly DependencyProperty PasswordTextProperty =
            DependencyProperty.Register(nameof(PasswordText), typeof(string), typeof(PasswordBoxWithToggle),
                new PropertyMetadata(string.Empty, OnPasswordTextChanged));

        public string PasswordText
        {
            get => (string)GetValue(PasswordTextProperty);
            set => SetValue(PasswordTextProperty, value);
        }

        private static void OnPasswordTextChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            if (d is PasswordBoxWithToggle control && control.PasswordBox.Password != (string)e.NewValue)
            {
                control.PasswordBox.Password = (string)e.NewValue;
            }
        }

        // Handle PasswordChanged event
        private void PasswordBox_PasswordChanged(object sender, RoutedEventArgs e)
        {
            if (PasswordBox.Password != PasswordText)
            {
                PasswordText = PasswordBox.Password;
            }
        }
    }
}
