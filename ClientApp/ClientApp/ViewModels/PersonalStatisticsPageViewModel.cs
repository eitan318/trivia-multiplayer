using ClientApp.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;

namespace ClientApp.ViewModels
{
    class PersonalStatisticsPageViewModel : BaseViewModel
    {
        public PersonalStatisticsPageViewModel(Page owner)
        {
            this.ownerPage = owner;
        }
        public static PersonalStatisticsPageViewModel Instance(Page owner)
        {
            return GetInstance(() => new PersonalStatisticsPageViewModel(owner));
        }
        private Page ownerPage;
        private string _errorMessage;
    }
}
