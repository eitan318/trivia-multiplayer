namespace ClientApp.Models
{
    public struct RoomPreview
    {
        public RoomData RoomData { get; set; }
        public uint CurrPlayersAmount { get; set; }
        public bool Status { get; set; }


        public string PlayersInfo => $"{CurrPlayersAmount}/{RoomData.MaxPlayers}";
    }

}
