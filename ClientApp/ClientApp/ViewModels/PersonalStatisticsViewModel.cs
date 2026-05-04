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
            PlayerRegularStats = new PersonalStatisticsModel();
            Player1v1Stats = new PersonalStatisticsModel();
        }


        public override void OnNavigatedTo()
        {
            SetStats();
        }


        // Fields
        private PersonalStatisticsModel playerRegularStats;
        private PersonalStatisticsModel player1v1Stats;

        // Error message fields
        private string _errorMessage;

        // Properties
        public PersonalStatisticsModel PlayerRegularStats
        {
            get => playerRegularStats;
            set
            {
                playerRegularStats = value;
                OnPropertyChanged();
            }
        }

        public PersonalStatisticsModel Player1v1Stats
        {
            get => player1v1Stats;
            set
            {
                player1v1Stats = value;
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
                    this.PlayerRegularStats = personalStatisticsResponse.Statistics.RegularStats;
                    this.Player1v1Stats = personalStatisticsResponse.Statistics.Stats1v1;
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
