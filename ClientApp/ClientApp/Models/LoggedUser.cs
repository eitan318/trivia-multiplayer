using System.ComponentModel;

namespace ClientApp.Models
{
    public class LoggedUser : INotifyPropertyChanged
    {
        private string _username;
        private bool _isMe;

        public string Username
        {
            get => _username;
            set
            {
                if (_username != value)
                {
                    _username = value;
                    OnPropertyChanged(nameof(Username));
                }
            }
        }

        public bool IsMe
        {
            get => _isMe;
            set
            {
                if (_isMe != value)
                {
                    _isMe = value;
                    OnPropertyChanged(nameof(IsMe));
                }
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}

