namespace ClientApp.Models
{
    public class PersonalStatisticsModel
    {
        public string UserName {  get; set; }
        private double avgAnswerTime;

        public double AvgAnswerTime
        {
            get => Math.Round(avgAnswerTime, 2); // Returns the value rounded to 2 decimal places.
            set => avgAnswerTime = value;        // Sets the value directly.
        }

        public int GamesPlayed {  get; set; }
        public int TotalAnswers { get; set; }
        public int TotalCorrectAnswers { get; set; }

    }
}