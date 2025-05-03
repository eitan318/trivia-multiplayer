using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models
{
    public class RoomData    {
        public uint Id { get; set; }
        public string RoomName { get; set; }
        public uint MaxPlayers { get; set; }
        public uint NumOfQuestionsInGame { get; set; }
        public uint TimePerQuestion { get; set; }

    }

}
