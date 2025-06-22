using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models
{
    class GetQuestionResponseData
    {
        public QuestionInfo Question { get; set; }
        public uint QuestionNumber { get; set; }
    }
}
