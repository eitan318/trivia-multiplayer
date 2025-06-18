using System.ComponentModel;
using ClientApp.Models;

namespace ClientApp.Stores
{
    /// <summary>
    /// Represents data about a room and notifies changes to its properties.
    /// </summary>
    class RoomDataStore : StoreBase
    {
        private RoomDataModel? _currentRoomData;

        public RoomDataModel? CurrentRoomData
        {
            get => _currentRoomData;
            set
            {
                if (_currentRoomData != value)
                {
                    _currentRoomData = value;
                    OnPropertyChanged(nameof(CurrentRoomData));
                }
            }
        }

    }
}
