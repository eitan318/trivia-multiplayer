using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;

namespace ClientApp.ViewModels
{
    class HighScoresPageViewModel : BaseViewModel
    {
        /// <summary>
        /// The page that owns this ViewModel. Used for navigation purposes.
        /// </summary>
        private Page ownerPage;
        private HighScoresPageViewModel(Page owner)
        {
            this.ownerPage = owner;
        }
        public static StatisticsPageViewModel Instance(Page owner)
        {
            return GetInstance(() => new HighScoresPageViewModel(owner));
        }
    }
}
