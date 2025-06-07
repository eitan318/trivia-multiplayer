
namespace ClientApp.Models.Requests
{
    
    class CreateRoomRequest : IRequest
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="CreateRoomRequest"/> class.
        /// </summary>
        /// <param name="roomName">The name of the room.</param>
        /// <param name="maxUsers">The maximum number of users allowed in the room.</param>
        /// <param name="questionCount">The number of questions in the room.</param>
        /// <param name="answerTimeout">The timeout in seconds for answering each question.</param>
        public CreateRoomRequest(string roomName, uint maxUsers, uint questionCount, double answerTimeout)
        {
            this.RoomName = roomName;
            this.MaxUsers = maxUsers;
            this.QuestionCount = questionCount;
            this.AnswerTimeout = answerTimeout;
        }

        public RequestsCodes GetCode() => RequestsCodes.CreateRoomRequest;

        public string RoomName { get; }
        public uint MaxUsers { get; }
        public uint QuestionCount { get; }
        public double AnswerTimeout { get; }
    }
}
