using ClientApp.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.RightsManagement;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp
{
    class GetQuestionResponseData
    {
        public uint QuestionNumber { get; set; }
        public QuestionInfo Question {  get; set; }
    }
}
