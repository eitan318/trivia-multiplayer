using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Windows.Threading;

public class CountdownTimerViewModel : INotifyPropertyChanged
{
    private TimeSpan _remainingTime;
    private DispatcherTimer _timer;
    private bool _isRunning;

    public event EventHandler TimerEnded; // Event to notify when the timer ends
    public event PropertyChangedEventHandler PropertyChanged;

    public CountdownTimerViewModel()
    {
        _timer = new DispatcherTimer
        {
            Interval = TimeSpan.FromSeconds(1) // Update every second
        };
        _timer.Tick += TimerTick;
    }

    public TimeSpan RemainingTime
    {
        get => _remainingTime;
        set
        {
            _remainingTime = value;
            OnPropertyChanged();
            OnPropertyChanged(nameof(FormattedTime));
        }
    }

    public string FormattedTime => RemainingTime.ToString(@"mm\:ss");

    private void TimerTick(object sender, EventArgs e)
    {
        if (RemainingTime.TotalSeconds > 0)
        {
            RemainingTime = RemainingTime.Subtract(TimeSpan.FromSeconds(1));
        }
        else
        {
            Pause();
            OnTimerEnded();
        }
    }

    public void Start()
    {
        if (!_isRunning)
        {
            _isRunning = true;
            _timer.Start();
            Console.WriteLine("Timer started"); // Debugging log
        }
    }

    public void Pause()
    {
        _isRunning = false;
        _timer.Stop();
        Console.WriteLine("Timer paused"); // Debugging log
    }

    public void Reset(uint seconds)
    {
        Pause();
        RemainingTime = TimeSpan.FromSeconds(seconds);
        Console.WriteLine($"Timer reset to {seconds} seconds"); // Debugging log
    }

    protected virtual void OnTimerEnded()
    {
        Console.WriteLine("Timer ended"); // Debugging log
        TimerEnded?.Invoke(this, EventArgs.Empty);
    }

    protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
    {
        PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
}
