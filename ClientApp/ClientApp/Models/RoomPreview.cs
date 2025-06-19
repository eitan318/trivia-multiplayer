namespace ClientApp.Models
{
    class RoomPreview
    {
        public RoomDataModel RoomData { get; set; }
        public uint CurrPlayersAmount { get; set; }
        public RoomStatus Status { get; set; }

        public string PlayersInfo => $"{CurrPlayersAmount}/{RoomData.MaxPlayers}";
        public string RoomDisplayName => $"{RoomData.RoomName} (#{RoomData.Id})";
        public string StatusInfo
        {
            get
            {
                return Status switch
                {
                    RoomStatus.Closing => "Closed - something went wrong",
                    RoomStatus.InGame => "InGame",
                    RoomStatus.NotInGame => "Available",
                    _ => "Unknown Status"
                };
            }
        }
    }
}
