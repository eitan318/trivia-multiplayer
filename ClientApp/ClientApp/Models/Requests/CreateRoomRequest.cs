using System;

namespace ClientApp.Models.Requests
{
    /// <summary>
    /// Represents a request to create a new room.
    /// </summary>
    class CreateRoomRequest : IRequest
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="CreateRoomRequest"/> class.
        /// </summary>
        /// <param name="roomName">The name of the room.</param>
        /// <param name="maxUsers">The maximum number of users allowed in the room.</param>
        /// <param name="questionCount">The number of questions in the room.</param>
        /// <param name="answerTimeout">The timeout in seconds for answering each question.</param>
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
