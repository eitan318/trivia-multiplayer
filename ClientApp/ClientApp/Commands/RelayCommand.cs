using System.Windows.Input;

namespace ClientApp.Commands
{
/// <summary>
/// Represents a command that can be bound to user interface actions.
/// </summary>
public class RelayCommand : ICommand
{
    private readonly Action<object> _execute;
    private readonly Func<object, bool> _canExecute;

    /// <summary>
    /// Occurs when the ability of the command to execute has changed.
    /// </summary>
    public event EventHandler CanExecuteChanged;

    /// <summary>
    /// Initializes a new instance of the <see cref="RelayCommand"/> class for commands with parameters.
    /// </summary>
    /// <param name="execute">The action to execute when the command is invoked.</param>
    /// <param name="canExecute">A function that determines whether the command can execute. Optional.</param>
    /// <exception cref="ArgumentNullException">Thrown if <paramref name="execute"/> is <c>null</c>.</exception>
    public RelayCommand(Action<object> execute, Func<object, bool> canExecute = null)
    {
        _execute = execute ?? throw new ArgumentNullException(nameof(execute));
        _canExecute = canExecute;
    }

    /// <summary>
    /// Initializes a new instance of the <see cref="RelayCommand"/> class for commands without parameters.
    /// </summary>
    /// <param name="execute">The action to execute when the command is invoked.</param>
    /// <param name="canExecute">A function that determines whether the command can execute. Optional.</param>
    /// <exception cref="ArgumentNullException">Thrown if <paramref name="execute"/> is <c>null</c>.</exception>
    public RelayCommand(Action execute, Func<bool> canExecute = null)
    {
        if (execute == null)
            throw new ArgumentNullException(nameof(execute));

        _execute =
            _ => execute();
        _canExecute = canExecute == null ? (Func<object, bool>)null :
                                         _ => canExecute();
    }

    /// <summary>
    /// Determines whether the command can execute in its current state.
    /// </summary>
    /// <param name="parameter">An optional parameter for the command. Can be <c>null</c>.</param>
    /// <returns><c>true</c> if the command can execute; otherwise, <c>false</c>.</returns>
    public bool CanExecute(object parameter) => _canExecute?.Invoke(parameter) ?? true;

    /// <summary>
    /// Executes the command.
    /// </summary>
    /// <param name="parameter">An optional parameter for the command. Can be <c>null</c>.</param>
    public void Execute(object parameter) => _execute(parameter);

    /// <summary>
    /// Raises the <see cref="CanExecuteChanged"/> event to notify the UI of changes in the command's execution status.
    /// </summary>
    public void RaiseCanExecuteChanged() => CanExecuteChanged?.Invoke(this, EventArgs.Empty);
}
}
