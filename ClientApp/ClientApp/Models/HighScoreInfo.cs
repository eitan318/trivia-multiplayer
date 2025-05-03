using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models
{
    /**
    * @struct HighScoreInfo
    * @brief A structure that holds information about a player's high score in a specific game.
    */
    public class HighScoreInfo
    {
        public string PlayerUsername {  get; set; }
        public string GameName {  get; set; }
        public int TotalScore {  get; set; }
        public uint GameId {  get; set; }
        public uint Rank {  get; set; }
    };
}
