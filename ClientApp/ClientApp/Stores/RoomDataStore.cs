using System.ComponentModel;
using ClientApp.Models;

namespace ClientApp.Stores
{
    /// <summary>
    /// Represents data about a room and notifies changes to its properties.
    /// </summary>
    public class RoomDataStore : StoreBase
    {
        private RoomDataModel? _currentRoom;

        public RoomDataModel? CurrentRoom
        {
            get => _currentRoom;
            set
            {
                if (_currentRoom != value)
                {
                    _currentRoom = value;
                    OnPropertyChanged(nameof(CurrentRoom));
                }
            }
        }

    }
}
