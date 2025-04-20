using ClientApp.Commands;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using ClientApp.ViewModels;
using ClientApp.Services;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Views.Pages;
using ClientApp.Views;

namespace ClientApp.ViewModels.ForgotPassword
{
    class ResetPasswordStepViewModel : BaseViewModel
    {
        private string _newPassword;
        public string NewPassword
        {
            get => _newPassword;
            set => SetProperty(ref _newPassword, value);
        }

        private string _confirmPassword;
        public string ConfirmPassword
        {
            get => _confirmPassword;
            set => SetProperty(ref _confirmPassword, value);
        }

        private string _errorMessage;
        public string ErrorMessage
        {
            get => _errorMessage;
            set => SetProperty(ref _errorMessage, value);
        }

        public string Username { get; set; }


        public ICommand ResetPasswordCommand { get; }

        public ResetPasswordStepViewModel()
        {
            ResetPasswordCommand = new RelayCommand(OnResetPassword);
        }

        private async void OnResetPassword()
        {
            if (NewPassword != ConfirmPassword)
            {
                ErrorMessage = "Need to be the same";
                return;
            }
            ResetPasswordRequest request = new ResetPasswordRequest(NewPassword, Username);
            ResponseInfo responseInfo = await RequestsExchangeService.ExchangeRequest(request);
            if(responseInfo.Code == (byte)ResponsesCodes.ErrorResponse)
            {
                ErrorResponse errorResponse = JsonResponseDeserialize.DeserializeResponse<ErrorResponse>(responseInfo);
                this.ErrorMessage = errorResponse.Message;
                return;
            }

            NoDataResponse response = JsonResponseDeserialize.DeserializeResponse<NoDataResponse>(responseInfo);
            if(response.Status == 0)
            {
                MyNavigationService.Navigate(new LoginPage());
                return;
            }
            else
            {
                string[] errMsgs =
                {
                    "",
                    "Unknown username" + request.Username,
                    "Invalid password. " + RegexFormats.Password,
                    "Invalid username" + request.Username
                };
                this.ErrorMessage = errMsgs[response.Status];
            }

        }
    }

}
