using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.ViewModels
{
    using System.ComponentModel;
    using System.Runtime.CompilerServices;

    public abstract class BaseViewModel : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        //Singleton Behaviur:
        private static readonly object _lock = new object();
        private static readonly Dictionary<Type, object> _instances = new();

        protected BaseViewModel() { }

        public static T GetInstance<T>(Func<T> factory = null) where T : BaseViewModel
        {
            var type = typeof(T);

            if (!_instances.ContainsKey(type))
            {
                lock (_lock)
                {
                    if (!_instances.ContainsKey(type))
                    {
                        if (factory == null)
                        {
                            throw new InvalidOperationException($"No factory provided for {type.Name}");
                        }
                        _instances[type] = factory();
                    }
                }
            }

            return (T)_instances[type];
        }

        protected void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

    }

}
