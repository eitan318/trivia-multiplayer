using System.ComponentModel;
using System.Runtime.CompilerServices;

namespace ClientApp.Models
{
    /// <summary>
    /// Model for storing room data.
    /// </summary>
    class RoomDataModel : INotifyPropertyChanged
    {
        private string _roomName;
        private uint _maxPlayers;
        private uint _numOfQuestionsInGame;
        private double _timePerQuestion;
        private double _scoreShowingTime;

        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        /// <summary>
        /// Copy constructor for creating a new instance from an existing RoomDataModel.
        /// </summary>
        /// <param name="other">The RoomDataModel instance to copy from.</param>
        public RoomDataModel(RoomDataModel other)
        {
            if (other == null) throw new ArgumentNullException(nameof(other));

            Id = other.Id;
            RoomName = other.RoomName;
            MaxPlayers = other.MaxPlayers;
            NumOfQuestionsInGame = other.NumOfQuestionsInGame;
            TimePerQuestion = other.TimePerQuestion;
            ScoreShowingTime = other.ScoreShowingTime;
        }

        public RoomDataModel()
        {
        }

        public uint Id { get; set; }

        public string RoomName
        {
            get => _roomName;
            set
            {
                if (_roomName != value)
                {
                    _roomName = value;
                    OnPropertyChanged();
                }
            }
        }

        public uint MaxPlayers
        {
            get => _maxPlayers;
            set
            {
                if (_maxPlayers != value)
                {
                    _maxPlayers = value;
                    OnPropertyChanged();
                }
            }
        }

        public uint NumOfQuestionsInGame
        {
            get => _numOfQuestionsInGame;
            set
            {
                if (_numOfQuestionsInGame != value)
                {
                    _numOfQuestionsInGame = value;
                    OnPropertyChanged();
                }
            }
        }
        public double ScoreShowingTime
        {
            get => _scoreShowingTime;
            set
            {
                if (_scoreShowingTime != value)
                {
                    _scoreShowingTime = value;
                    OnPropertyChanged();
                }
            }
        }

        public double TimePerQuestion
        {
            get => _timePerQuestion;
            set
            {
                if (_timePerQuestion != value)
                {
                    _timePerQuestion = value;
                    OnPropertyChanged();
                }
            }
        }
    }
}


