using System.Windows;
using System.Windows.Controls;

namespace ClientApp.Views.Controls
{
    /// <summary>
    /// A custom control that wraps a <see cref="PasswordBox"/> and a <see cref="TextBox"/> for password visibility toggle.
    /// </summary>
    public partial class PasswordBoxWithToggle : UserControl
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="PasswordBoxWithToggle"/> class.
        /// </summary>
        public PasswordBoxWithToggle()
        {
            InitializeComponent();
        }

        #region Dependency Properties

        public static readonly DependencyProperty InnerPasswordBoxStyleProperty =
            DependencyProperty.Register(nameof(InnerPasswordBoxStyle), typeof(Style), typeof(PasswordBoxWithToggle),
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

        public static readonly DependencyProperty InnerTextBoxStyleProperty =
            DependencyProperty.Register(nameof(InnerTextBoxStyle), typeof(Style), typeof(PasswordBoxWithToggle),
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

        public static readonly DependencyProperty IsPasswordVisibleProperty =
            DependencyProperty.Register(nameof(IsPasswordVisible), typeof(bool), typeof(PasswordBoxWithToggle),
                new PropertyMetadata(false));

        public bool IsPasswordVisible
        {
            get => (bool)GetValue(IsPasswordVisibleProperty);
            set => SetValue(IsPasswordVisibleProperty, value);
        }

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
            if (d is PasswordBoxWithToggle control)
            {
                var newPassword = e.NewValue as string;
                if (control.PasswordBox.Password != newPassword)
                {
                    control.PasswordBox.Password = newPassword;
                }

                if (control.VisiblePasswordBox.Text != newPassword)
                {
                    control.VisiblePasswordBox.Text = newPassword;
                }
            }
        }

        #endregion

        #region Event Handlers

        private void PasswordBox_PasswordChanged(object sender, RoutedEventArgs e)
        {
            if (PasswordBox.Password != PasswordText)
            {
                PasswordText = PasswordBox.Password;
            }
        }

        private void VisiblePasswordBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (VisiblePasswordBox.Text != PasswordText)
            {
                PasswordText = VisiblePasswordBox.Text;
            }
        }

        #endregion
    }
}
