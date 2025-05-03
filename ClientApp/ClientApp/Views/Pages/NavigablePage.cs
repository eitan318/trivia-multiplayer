using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;

namespace ClientApp.Views.Pages
{
    /// <summary>
    /// A navigable page that includes a back button for navigation to its parent page.
    /// </summary>
    public class NavigablePage : Page
    {
        private readonly Page _parentPage;

        /// <summary>
        /// Initializes a new instance of the <see cref="NavigablePage"/> class.
        /// </summary>
        /// <param name="parentPage">The parent page to navigate back to.</param>
        public NavigablePage(Page parentPage) : base()
        {
            _parentPage = parentPage;
            Loaded += OnPageLoaded;
        }

        /// <summary>
        /// Handles the Loaded event of the page.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The event data.</param>
        private void OnPageLoaded(object sender, RoutedEventArgs e)
        {
            AddBackButton(); // Add a back button to the page when loaded
        }

        /// <summary>
        /// Adds a back button to the page's grid content.
        /// </summary>
        /// <exception cref="InvalidOperationException">
        /// Thrown if the Content of the page is not a <see cref="Grid"/>.
        /// </exception>
        private void AddBackButton()
        {
            Button backButton = new Button
            {
                Content = "Back", // Button label
                HorizontalAlignment = HorizontalAlignment.Left,
                VerticalAlignment = VerticalAlignment.Top,
                Margin = new Thickness(10) // Add some spacing
            };

            backButton.Click += BackButton_Click; // Subscribe to Click event for navigation

            // Ensure Content is a Grid and add the button
            if (Content is Grid grid)
            {
                grid.Children.Add(backButton); // Add the back button to the grid
            }
            else
            {
                // Handle cases where Content isn't a Grid
                throw new InvalidOperationException("NavigablePage expects a Grid as its Content.");
            }
        }

        /// <summary>
        /// Handles the Click event of the back button.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The event data.</param>
        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            if (_parentPage != null)
            {
                NavigationService.Navigate(_parentPage); // Navigate to the parent page
            }
        }
    }
}
