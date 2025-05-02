using ClientApp.ViewModels;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using ClientApp.ViewModels.ForgotPassword;
using ClientApp.Views.Controls;

namespace ClientApp.Views.Pages
{
    /// <summary>
    /// Interaction logic for ForgotPasswordPage.xaml
    /// </summary>
    partial class ForgotPasswordPage : NavigablePage
    {
        public ForgotPasswordPage(Page parent) : base(parent)
        {
            InitializeComponent();
            ForgotPasswordViewModel vm = ForgotPasswordViewModel.Instance();
            vm.GoToEmailStep();
            DataContext = vm;

        }

        private void TextBox_PreviewTextInput(object sender, TextCompositionEventArgs e)
        {
            if (sender is TextBox textBox)
            {
                if (!char.IsDigit(e.Text, 0))
                {
                    e.Handled = true;
                    return;
                }
                textBox.Text = e.Text;
                var parentPanel = FindParentPanel(textBox);

                if (parentPanel != null)
                {
                    var textBoxes = GetChildControls<TextBox>(parentPanel).ToList();
                    var index = textBoxes.IndexOf(textBox);
                    if (index + 1 < textBoxes.Count && e.Text.Length == 1)
                    {
                        textBoxes[index + 1].Focus();
                        e.Handled = true;
                    }
                }
            }
        }

        private void TextBox_PreviewKeyDown(object sender, KeyEventArgs e)
        {
            if (sender is TextBox textBox)
            {
                var parentPanel = FindParentPanel(textBox);

                if (parentPanel != null)
                {
                    var textBoxes = GetChildControls<TextBox>(parentPanel).ToList();
                    var index = textBoxes.IndexOf(textBox);

                    if (e.Key == Key.Back)
                    {
                        e.Handled = true;
                        textBox.Clear();
                        if (index > 0)
                        {
                            var previousTextBox = textBoxes[index - 1];
                            previousTextBox.Focus();
                            previousTextBox.Clear(); // Optionally clear the previous TextBox
                        }
                    }
                }
            }
        }

        private Panel FindParentPanel(DependencyObject child)
        {
            DependencyObject parent = VisualTreeHelper.GetParent(child);

            while (parent != null && parent is not Panel)
            {
                parent = VisualTreeHelper.GetParent(parent);
            }

            return parent as Panel;
        }

        private IEnumerable<T> GetChildControls<T>(DependencyObject parent) where T : DependencyObject
        {
            if (parent == null) yield break;

            for (int i = 0; i < VisualTreeHelper.GetChildrenCount(parent); i++)
            {
                var child = VisualTreeHelper.GetChild(parent, i);

                if (child is T tChild)
                {
                    yield return tChild;
                }

                foreach (var descendant in GetChildControls<T>(child))
                {
                    yield return descendant;
                }
            }
        }

    }
}
