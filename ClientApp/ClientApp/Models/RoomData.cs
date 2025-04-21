using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models
{
    public struct RoomData
    {
        public uint id;
        public string name;
        public uint maxPlayers;
        public uint numOfQuestionsInGame;
        public uint timePerQuestion;
        public bool status;
    };
}
