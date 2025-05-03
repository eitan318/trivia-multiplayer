using ClientApp.Commands;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Models;
using ClientApp.Services;
using ClientApp.ViewModels;
using ClientApp.Views.Pages;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Input;
using System.Diagnostics.CodeAnalysis;

namespace ClientApp.ViewModels
{

    class HighScoresPageViewModel : BaseViewModel
    {
        private HighScoresPageViewModel()
        {
            RefreshTopCommand = new RelayCommand(RefreshTop);
            RefreshTop();
        }
        public static HighScoresPageViewModel Instance()
        {
            return GetInstance(() => new HighScoresPageViewModel());
        }
        /// <summary>
        /// The page that owns this ViewModel. Used for navigation purposes.
        /// </summary>
        private List<HighScoreInfo> responseList;
        private string _errorMessage;
        public string ErrorMessage
        {
            get => _errorMessage;
            set
            {
                _errorMessage = value;
                OnPropertyChanged();
            }
        }
        public List<HighScoreInfo> ResponseList
        {
            get => responseList;
            set
            {
                responseList = value;
                OnPropertyChanged();
            }
        }


        public ICommand RefreshTopCommand { get; }



        /// <summary>
        /// This function refreshes the top leading players
        /// </summary>
        public async void RefreshTop()
        { 
            try
            {
                HighScoresRequest request = new HighScoresRequest(3);
                var responseInfo = await RequestsExchangeService.ExchangeRequest(request);

                if (responseInfo.Code == (byte)ResponsesCodes.ErrorResponse)
                {
                    var error = JsonResponseDeserialize.DeserializeResponse<ErrorResponse>(responseInfo);
                    return;
                }

                var HighestScoresResponse = 
                    JsonResponseDeserialize.DeserializeResponse<HighScoresResponse>(responseInfo);
                this.ResponseList = HighestScoresResponse.Statistics;
            }
            catch (Exception ex)
            {
                ErrorMessage = $"Error retrieving top users: {ex.Message}";
            }
        }

    }
}
