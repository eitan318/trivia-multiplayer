using System;
using System.Windows;
using System.Windows.Controls;

namespace ClientApp
{
    public class ViewModelToPageTemplateSelector : DataTemplateSelector
    {
        public override DataTemplate SelectTemplate(object item, DependencyObject container)
        {
            if (item == null) return null;

            var frameworkElement = container as FrameworkElement;

            // Extract the ViewModel name (e.g., LoginViewModel -> LoginView)
            var viewModelName = item.GetType().FullName;
            var viewName = viewModelName.Replace("ViewModels", "Views.Screens").Replace("ViewModel", "View");

            // Dynamically find the View by name in the same namespace
            var viewType = Type.GetType(viewName);
            if (viewType != null)
            {
                var viewInstance = Activator.CreateInstance(viewType) as FrameworkElement;
                var dataTemplate = new DataTemplate
                {
                    VisualTree = new FrameworkElementFactory(viewInstance.GetType())
                };
                return dataTemplate;
            }

            // Fallback: Look for a DataTemplate with a matching key (Look for view)
            return frameworkElement?.FindResource(viewModelName) as DataTemplate;
        }
    }
}
