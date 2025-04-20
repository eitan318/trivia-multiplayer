using ClientApp.Models.Requests;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Responses
{
    class ErrorResponse
    {
        //public ErrorResponse(string message) { 
        //    this.Message = message;
        //}
        public ResponsesCodes GetCode() => ResponsesCodes.ErrorResponse;
        public string Message { get; set; }
    }
}
