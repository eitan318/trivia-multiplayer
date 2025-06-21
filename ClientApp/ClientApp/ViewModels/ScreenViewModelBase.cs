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
        protected ScreenViewModelBase(bool hasBackBtn = false) 
        {
            this.HasBackBtn = hasBackBtn;
        }

        public virtual void OnNavigatedTo() { }
        public virtual void OnNavigatedAway() { }

        public virtual void Dispose() { }

        public bool HasBackBtn { get; private set; }



    }
}
