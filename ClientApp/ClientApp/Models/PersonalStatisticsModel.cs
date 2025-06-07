namespace ClientApp.Models
{
    public class PersonalStatisticsModel
    {
        public string UserName {  get; set; }
        public double AvgAnswerTime { get; set; }
        public int GamesPlayed {  get; set; }
        public int TotalAnswers { get; set; }
        public int TotalCorrectAnswers { get; set; }

    }
}