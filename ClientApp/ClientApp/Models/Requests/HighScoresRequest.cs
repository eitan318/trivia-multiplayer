namespace ClientApp.Models.Requests
{
    
    class HighScoresRequest : IRequest
    {
        public HighScoresRequest(int topPlayersLimit)
        {
            this.TopPlayersLimit = topPlayersLimit;
        }
        public RequestsCodes GetCode() => RequestsCodes.GetHighScoresRequest;
        public int TopPlayersLimit;
    }
}
