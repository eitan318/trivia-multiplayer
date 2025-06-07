namespace ClientApp.Models
{
    public struct RoomPreview
    {
        public RoomDataModel RoomData { get; set; }
        public uint CurrPlayersAmount { get; set; }
        public bool Status { get; set; }


        public string PlayersInfo => $"{CurrPlayersAmount}/{RoomData.MaxPlayers}";
    }

}
