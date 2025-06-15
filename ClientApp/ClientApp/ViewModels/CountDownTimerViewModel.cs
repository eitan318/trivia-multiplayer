using System;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Timers;
using System.Windows;

namespace ClientApp.ViewModels
{
    class CountdownTimerViewModel : INotifyPropertyChanged, IDisposable
    {
        private TimeSpan _remainingTime;
        private readonly System.Timers.Timer _timer;
        private int _msInterval;

        public event EventHandler TimerEnded;
        public event PropertyChangedEventHandler PropertyChanged;

        public CountdownTimerViewModel(int msInverval)
        {
            _timer = new System.Timers.Timer(msInverval); 
            _timer.Elapsed += TimerElapsed;
            this._msInterval = msInverval;
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

        public bool IsRunning => _timer.Enabled;

        private void TimerElapsed(object sender, ElapsedEventArgs e)
        {
            RemainingTime -= TimeSpan.FromMilliseconds(_msInterval);
            
            if (RemainingTime > TimeSpan.Zero)
            {
                // Update the UI on the main thread
                Application.Current.Dispatcher.Invoke(() =>
                {
                    OnPropertyChanged(nameof(FormattedTime));
                });
            }
            else
            {
                Stop();
                RemainingTime = TimeSpan.Zero;
                TimerEnded?.Invoke(this, EventArgs.Empty);
            }
        }

        public void Start()
        {
            if (!IsRunning)
            {
                _timer.Start();
            }
        }

        public void Stop()
        {
            if (IsRunning)
            {
                _timer.Stop();
            }
        }

        public void Reset(TimeSpan newTime)
        {
            Stop();
            RemainingTime = newTime;
        }

        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        public void Dispose()
        {
            _timer.Elapsed -= TimerElapsed;
            _timer.Stop();
            _timer.Dispose();
        }
    }
}
