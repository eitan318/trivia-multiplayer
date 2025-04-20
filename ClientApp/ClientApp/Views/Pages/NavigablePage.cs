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

namespace ClientApp.Views.Pages
{
    public class NavigablePage : Page
    {
        private readonly Page _parentPage;

        public NavigablePage(Page parentPage) : base()
        {
            _parentPage = parentPage;
            Loaded += OnPageLoaded;

        }

        private void OnPageLoaded(object sender, RoutedEventArgs e)
        {
            AddBackButton();
        }


        private void AddBackButton()
        {
            Button backButton = new Button
            {
                Content = "Back",
                HorizontalAlignment = HorizontalAlignment.Left,
                VerticalAlignment = VerticalAlignment.Top,
                Margin = new Thickness(10)
            };

            backButton.Click += BackButton_Click;

            // Ensure Content is a Grid and add the button
            if (Content is Grid grid)
            {
                grid.Children.Add(backButton);
            }
            else
            {
                // Optionally log or handle cases where Content isn't a Grid
                throw new InvalidOperationException("NavigablePage expects a Grid as its Content.");
            }
        }

        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            if (_parentPage != null)
            {
                NavigationService.Navigate(_parentPage);
            }
        }
    }

}
