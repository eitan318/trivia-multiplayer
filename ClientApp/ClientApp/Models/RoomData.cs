using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models
{
    public struct RoomData
    {
        private uint id;
        public string name;
        public uint maxPlayers;
        public uint numOfQuestionsInGame;
        public uint timePerQuestion;
        public bool status;

        public uint Id { get => id; set => id = value; }
    };
}
