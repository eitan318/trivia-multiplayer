using ClientApp.Commands;
using ClientApp.Models;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using System.Windows.Input;

namespace ClientApp.ViewModels
{
    class PersonalStatisticsViewModel : ScreenViewModelBase
    {
        private readonly RequestsExchangeService _requestsExchangeService;
        public PersonalStatisticsViewModel(
            RequestsExchangeService requestsExchangeService,
            TopBarViewModel topBarViewModel) : base(true, topBarViewModel)
        {
            _requestsExchangeService = requestsExchangeService;
            this.personalInfo = new PersonalStatisticsModel();
        }


        public override void OnNavigatedTo()
        {
            SetStats();
        }


        // Fields
        private PersonalStatisticsModel personalInfo;

        // Error message fields
        private string _errorMessage;

        // Properties
        public PersonalStatisticsModel PersonalInfo
        {
            get => personalInfo;
            set
            {
                personalInfo = value;
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



        public async void SetStats()
        {
            try
            {
                var responseInfo = await _requestsExchangeService.ExchangeRequest<PersonalStatisticsResponse>(RequestsCodes.PersonalStatisticsRequest);

                if (responseInfo.NormalResponse)
                {
                      var personalStatisticsResponse = responseInfo.Response;
                    this.PersonalInfo = personalStatisticsResponse.Statistics;
                }
                else
                {

                }
            }
            catch (Exception ex)    
            {
                ErrorMessage = $"Error retrieving data on user: {ex.Message}";
            }
        }

    }
}
