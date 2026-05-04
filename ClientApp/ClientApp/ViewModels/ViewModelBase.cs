
namespace ClientApp.ViewModels
{
    using System.ComponentModel;
    using System.Runtime.CompilerServices;

    /// <summary>
    /// The base class for all view models in the application. Implements the INotifyPropertyChanged interface 
    /// to support data binding and property change notification. It also provides singleton behavior for view models.
    /// </summary>
    public abstract class ViewModelBase : INotifyPropertyChanged, IDisposable
    {
        /// <summary>
        /// Event raised whenever a property value changes, allowing subscribers to respond to the change.
        /// </summary>
        public event PropertyChangedEventHandler PropertyChanged;

        /// <summary>
        /// Notifies subscribers that a property value has changed. This method is intended to be called in property setters.
        /// </summary>
        /// <param name="propertyName">The name of the property that changed (automatically inferred by caller).</param>
        protected void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        public virtual void Dispose() { }

    }
}
