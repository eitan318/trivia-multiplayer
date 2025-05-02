using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models
{
    public struct PersonalStatistics
    {
        public string username {  get; set; }
        public int totalCorrectAnswers {  get; set; }
        public int gamesPlayed {  get; set; }
        public int totalAnswers { get; set; }
        public double avgAnswerTime {  get; set; }

    }
}