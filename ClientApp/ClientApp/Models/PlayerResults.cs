namespace ClientApp.Models
{
    class PlayerResults
    {
        public string Username { get; set; }
        public uint CorrectAnswerCount {get; set; }
        public uint WrongAnswerCount {get; set; }
        public double AverageAnswerTime {get; set; }
        
    }
}
