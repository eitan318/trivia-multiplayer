
namespace ClientApp.ViewModels
{
    using System.ComponentModel;
    using System.Runtime.CompilerServices;

    /// <summary>
    /// The base class for all view models in the application. Implements the INotifyPropertyChanged interface 
    /// to support data binding and property change notification. It also provides singleton behavior for view models.
    /// </summary>
    public abstract class BaseViewModel : INotifyPropertyChanged
    {
        /// <summary>
        /// Event raised whenever a property value changes, allowing subscribers to respond to the change.
        /// </summary>
        public event PropertyChangedEventHandler PropertyChanged;

        // Singleton Behavior

        private static readonly object _lock = new object();
        private static readonly Dictionary<Type, object> _instances = new();

        /// <summary>
        /// Protected constructor for derived classes to ensure that only classes inheriting from BaseViewModel 
        /// can be instantiated.
        /// </summary>
        protected BaseViewModel() { }

        /// <summary>
        /// Provides a singleton instance of the specified view model type.
        /// If no instance exists, a new one is created using the provided factory.
        /// </summary>
        /// <typeparam name="T">The type of the view model (must be derived from BaseViewModel).</typeparam>
        /// <param name="factory">An optional factory function to create the view model instance. 
        /// If not provided, an exception is thrown when no instance exists.</param>
        /// <returns>The singleton instance of the view model.</returns>
        /// <exception cref="InvalidOperationException">
        /// Thrown if no factory is provided and an instance for the specified type does not already exist.
        /// </exception>
        public static T GetInstance<T>(Func<T> factory = null) where T : BaseViewModel
        {
            var type = typeof(T);

            // Check if instance already exists
            if (!_instances.ContainsKey(type))
            {
                lock (_lock)
                {
                    // Double-check to avoid race conditions
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

        /// <summary>
        /// Notifies subscribers that a property value has changed. This method is intended to be called in property setters.
        /// </summary>
        /// <param name="propertyName">The name of the property that changed (automatically inferred by caller).</param>
        protected void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
