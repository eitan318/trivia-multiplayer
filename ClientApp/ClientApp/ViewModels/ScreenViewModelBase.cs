using ClientApp.Views.Controls;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.ViewModels
{
    public class ScreenViewModelBase : ViewModelBase
    {
        // Singleton Behavior

        private static readonly object _lock = new object();
        private static readonly Dictionary<Type, object> _instances = new();

        /// <summary>
        /// Protected constructor for derived classes to ensure that only classes inheriting from BaseViewModel 
        /// can be instantiated.
        /// </summary>
        protected ScreenViewModelBase(bool hasBackBtn = false, TopBarViewModel? topBarViewModel = null) 
        {

            HasNavBar = topBarViewModel != null;
            if (HasNavBar)
            {
                this.NavBarVM = topBarViewModel;
            }
            WindowBackBtn = hasBackBtn;
            NavBarBackBtn = hasBackBtn;
            if (hasBackBtn)
            {
                if(HasNavBar)
                {
                    WindowBackBtn = false;
                }
                else
                {
                    NavBarBackBtn = false;
                }
            }
        }

        public virtual void OnNavigatedTo() { }
        public virtual void OnNavigatedAway() { }



        public bool WindowBackBtn { get; private set; }
        public TopBarViewModel NavBarVM { get; private set; }
        public bool HasNavBar { get; private set; }
        public bool NavBarBackBtn { get; private set; }



    }
}
