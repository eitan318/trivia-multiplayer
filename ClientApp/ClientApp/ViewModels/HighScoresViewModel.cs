using ClientApp.Commands;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Models;
using ClientApp.Services;
using System.Windows.Input;

namespace ClientApp.ViewModels
{

    class HighScoresViewModel : ViewModelBase
    {
        public HighScoresViewModel()
        {
            RefreshTopCmd = new RelayCommand(RefreshTop);
            RefreshTop();
        }
        // Fields
        private List<HighScoreInfo> responseList;
        
        // Error mesasge fields
        private string _errorMessage;

        // Properties

        public List<HighScoreInfo> ResponseList
        {
            get => responseList;
            set
            {
                responseList = value;
                OnPropertyChanged();
            }
        }
        
        
        // Error message properties
        public string ErrorMessage
        {
            get => _errorMessage;
            set
            {
                _errorMessage = value;
                OnPropertyChanged();
            }
        }

        //Commands
        public ICommand RefreshTopCmd { get; }



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
