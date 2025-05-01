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

        /// <summary>
        /// Dependency property for <see cref="InnerPasswordBoxStyle"/>.
        /// </summary>
        public static readonly DependencyProperty InnerPasswordBoxStyleProperty =
            DependencyProperty.Register(
                nameof(InnerPasswordBoxStyle),
                typeof(Style),
                typeof(PasswordBoxWithToggle),
                new PropertyMetadata(null, OnInnerPasswordBoxStyleChanged));

        /// <summary>
        /// Gets or sets the style for the inner <see cref="PasswordBox"/>.
        /// </summary>
        public Style InnerPasswordBoxStyle
        {
            get => (Style)GetValue(InnerPasswordBoxStyleProperty);
            set => SetValue(InnerPasswordBoxStyleProperty, value);
        }

        /// <summary>
        /// Callback when the <see cref="InnerPasswordBoxStyle"/> dependency property changes.
        /// </summary>
        private static void OnInnerPasswordBoxStyleChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            if (d is PasswordBoxWithToggle control && e.NewValue is Style newStyle)
            {
                control.PasswordBox.Style = newStyle;
            }
        }

        /// <summary>
        /// Dependency property for <see cref="InnerTextBoxStyle"/>.
        /// </summary>
        public static readonly DependencyProperty InnerTextBoxStyleProperty =
            DependencyProperty.Register(
                nameof(InnerTextBoxStyle),
                typeof(Style),
                typeof(PasswordBoxWithToggle),
                new PropertyMetadata(null, OnInnerTextBoxStyleChanged));

        /// <summary>
        /// Gets or sets the style for the inner <see cref="TextBox"/> used to display the password in plain text.
        /// </summary>
        public Style InnerTextBoxStyle
        {
            get => (Style)GetValue(InnerTextBoxStyleProperty);
            set => SetValue(InnerTextBoxStyleProperty, value);
        }

        /// <summary>
        /// Callback when the <see cref="InnerTextBoxStyle"/> dependency property changes.
        /// </summary>
        private static void OnInnerTextBoxStyleChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            if (d is PasswordBoxWithToggle control && e.NewValue is Style newStyle)
            {
                control.VisiblePasswordBox.Style = newStyle;
            }
        }

        /// <summary>
        /// Dependency property for <see cref="IsPasswordVisible"/>.
        /// </summary>
        public static readonly DependencyProperty IsPasswordVisibleProperty =
            DependencyProperty.Register(nameof(IsPasswordVisible), typeof(bool), typeof(PasswordBoxWithToggle), new PropertyMetadata(false));

        /// <summary>
        /// Gets or sets a value indicating whether the password is visible.
        /// </summary>
        public bool IsPasswordVisible
        {
            get => (bool)GetValue(IsPasswordVisibleProperty);
            set => SetValue(IsPasswordVisibleProperty, value);
        }

        /// <summary>
        /// Dependency property for <see cref="PasswordText"/>.
        /// </summary>
        public static readonly DependencyProperty PasswordTextProperty =
            DependencyProperty.Register(nameof(PasswordText), typeof(string), typeof(PasswordBoxWithToggle),
                new PropertyMetadata(string.Empty, OnPasswordTextChanged));

        /// <summary>
        /// Gets or sets the password text as a string.
        /// </summary>
        public string PasswordText
        {
            get => (string)GetValue(PasswordTextProperty);
            set => SetValue(PasswordTextProperty, value);
        }

        #endregion

        #region Event Handlers

        /// <summary>
        /// Callback when the <see cref="PasswordText"/> dependency property changes.
        /// </summary>
        private static void OnPasswordTextChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            if (d is PasswordBoxWithToggle control && control.PasswordBox.Password != (string)e.NewValue)
            {
                control.PasswordBox.Password = (string)e.NewValue;
            }
        }

        /// <summary>
        /// Event handler for the <see cref="PasswordBox.PasswordChanged"/> event.
        /// Updates the <see cref="PasswordText"/> when the password changes.
        /// </summary>
        private void PasswordBox_PasswordChanged(object sender, RoutedEventArgs e)
        {
            if (PasswordBox.Password != PasswordText)
            {
                PasswordText = PasswordBox.Password;
            }
        }

        #endregion
    }
}
