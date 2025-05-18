using System.Windows.Controls;

namespace ClientApp.Services
{
    class MyNavigationService
    {
        private static Frame _frame;
        public static void Initialize(Frame frame)
        {
            _frame = frame;
        }
        public static void Navigate(Page page)
        {
            _frame.Navigate(page);
        }
    }
}
