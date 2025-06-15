using System;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Windows.Threading;

namespace ClientApp.ViewModels
{
    class CountdownTimerViewModel : INotifyPropertyChanged, IDisposable
    {
        private TimeSpan _remainingTime;
        private readonly DispatcherTimer _timer;

        public event EventHandler TimerEnded;
        public event PropertyChangedEventHandler PropertyChanged;

        public CountdownTimerViewModel()
        {
            _timer = new DispatcherTimer
            {
                Interval = TimeSpan.FromSeconds(1)
            };
            _timer.Tick += TimerTick;

            Console.WriteLine("CountdownTimer initialized.");
        }

        public TimeSpan RemainingTime
        {
            get => _remainingTime;
            private set
            {
                if (_remainingTime != value)
                {
                    _remainingTime = value;
                    OnPropertyChanged();
                    OnPropertyChanged(nameof(FormattedTime));
                }
            }
        }

        public string FormattedTime => RemainingTime.ToString(@"mm\:ss");

        public bool IsRunning => _timer.IsEnabled;

        private async void TimerTick(object sender, EventArgs e)
        {
            if (RemainingTime > TimeSpan.Zero)
            {
                RemainingTime -= _timer.Interval;
                Console.WriteLine($"Timer ticked. Remaining time: {FormattedTime}");
            }
            else
            {
                Stop();
                RemainingTime = TimeSpan.Zero;
                Console.WriteLine("Timer ended.");
                TimerEnded?.Invoke(this, EventArgs.Empty);
            }
        }

        public async void Start()
        {
            if (!IsRunning)
            {
                _timer.Start();
                Console.WriteLine("Timer started.");
            }
        }

        public async void Stop()
        {
            if (IsRunning)
            {
                _timer.Stop();
                Console.WriteLine("Timer stopped.");
            }
        }

        public async void Reset(TimeSpan newTime)
        {
            Stop();
            RemainingTime = newTime;
            Console.WriteLine($"Timer reset to: {FormattedTime}");
        }

        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        public async void Dispose()
        {
            _timer.Tick -= TimerTick;
            _timer.Stop();
            Console.WriteLine("CountdownTimer disposed.");
        }
    }
}
