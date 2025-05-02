using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models
{
    public class PersonalStatistics
    {
        public string UserName {  get; set; }
        public double AvgAnswerTime { get; set; }
        public int GamesPlayed {  get; set; }
        public int TotalAnswers { get; set; }
        public int TotalCorrectAnswers { get; set; }

    }
}