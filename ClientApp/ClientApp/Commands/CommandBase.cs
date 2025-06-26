using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using ClientApp.Extensions;

namespace ClientApp.Commands
{
    public interface IAsyncCommand : ICommand
    {
        Task ExecuteAsync(object parameter);
    }

    public abstract class CommandBase : ICommand
    {
        public event EventHandler CanExecuteChanged;

        public virtual bool CanExecute(object parameter) => true;

        public virtual void Execute(object parameter)
        {
            ExecuteAsync(parameter).FireAndForgetSafeAsync(); 
        }
        public virtual Task ExecuteAsync(object parameter)
        {
            return Task.CompletedTask; 
        }

        public void RaiseCanExecuteChanged()
        {
            CanExecuteChanged?.Invoke(this, new EventArgs());
        }
    }
}
