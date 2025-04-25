using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Requests
{
    class CreateRoomRequest : IRequest
    {
        public CreateRoomRequest(string roomName, uint maxUsers, uint questionCount, uint answerTimeout)
        {
            RoomName = roomName;
            MaxUsers = maxUsers;
            QuestionCount = questionCount;
            AnswerTimeout = answerTimeout;
        }
        public RequestsCodes GetCode() => RequestsCodes.CreateRoomRequest;
        public string RoomName { get; set; }
        public uint MaxUsers { get; set; }
        public uint QuestionCount { get; set; }
        public uint AnswerTimeout { get; set; }
    }
}
