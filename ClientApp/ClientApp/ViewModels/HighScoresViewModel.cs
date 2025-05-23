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
        private readonly RequestsExchangeService _requestsExchangeService;
        public HighScoresViewModel(RequestsExchangeService requestsExchangeService) : base(true)
        {
            RefreshTopCmd = new RelayCommand(RefreshTop);
            _requestsExchangeService = requestsExchangeService;
            RefreshTop();
        }
        // Fields
        private List<HighScoreInfoModel> responseList;
        
        // Error mesasge fields
        private string _errorMessage;

        // Properties

        public List<HighScoreInfoModel> ResponseList
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
                var responseInfo = await _requestsExchangeService.ExchangeRequest(request);

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
