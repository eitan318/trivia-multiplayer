namespace ClientApp.Models
{
    public class PlayerResults
    {
        public string Username { get; set; }
        public uint CorrectAnswerCount {get; set; }
        public uint WrongAnswerCount {get; set; }
        public double AverageAnswerTime {get; set; }
        
    }
}
