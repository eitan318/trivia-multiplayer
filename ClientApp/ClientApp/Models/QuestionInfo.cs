
namespace ClientApp.Models
{
    class QuestionInfo
    {
        public string Difficulty { get; set; }
        public string Category { get; set; }
        public string Question { get; set; }
        public List<string> PossibleAnswers { get; set; }
    }
}
