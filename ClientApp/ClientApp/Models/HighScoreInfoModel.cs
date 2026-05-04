
namespace ClientApp.Models
{
    /**
    * @struct HighScoreInfo
    * @brief A structure that holds information about a player's high score in a specific game.
    */
    public class HighScoreInfoModel
    {
        public string PlayerUsername {  get; set; }
        public string RoomName {  get; set; }
        public string StartTime {  get; set; }
        public int TotalScore {  get; set; }
        public uint GameId {  get; set; }
        public uint Rank {  get; set; }
    };
}
