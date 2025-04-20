using ClientApp.Commands;
using ClientApp.Services;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;

namespace ClientApp.ViewModels.ForgotPassword
{
    class EmailStepViewModel : BaseViewModel
    {
        private readonly ForgotPasswordViewModel _parent;

        public EmailStepViewModel(ForgotPasswordViewModel parent)
        {
            _parent = parent;
            SubmitEmailCommand = new RelayCommand(SubmitEmail);
        }

        public string Email { get; set; }
        public ICommand SubmitEmailCommand { get; }


        private string _errorMessage;
        public string ErrorMessage
        {
            get => _errorMessage;
            set => SetProperty(ref _errorMessage, value);
        }


        private async void SubmitEmail()
        {
            if (string.IsNullOrEmpty(Email)) {
                ErrorMessage = "Email field cannot be empty";
                return;
            }
            ForgotPasswordRequest request = new ForgotPasswordRequest(Email);
            ResponseInfo responseInfo = await RequestsExchangeService.ExchangeRequest(request);
            if (responseInfo.Code == (byte)ResponsesCodes.ErrorResponse) {
                ErrorResponse errorResponse = JsonResponseDeserialize.DeserializeResponse<ErrorResponse>(responseInfo);
                ErrorMessage = errorResponse.Message;
                return;
            }
            ForgotPasswordResponse response = JsonResponseDeserialize.DeserializeResponse<ForgotPasswordResponse>(responseInfo);
            if(response.Status == 0)
            {
                _parent.GoToCodeStep(response.EmailCode, response.Username);
            }
            else
            {
                string[] errMsg =
                {
                    "",
                    "Email does not exist",
                    "Invalid Email Format",
                };
                ErrorMessage = errMsg[response.Status];

            }

        }
    }
}
