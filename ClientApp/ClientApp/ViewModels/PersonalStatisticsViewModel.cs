using ClientApp.Commands;
using ClientApp.Models;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using System.Windows.Input;

namespace ClientApp.ViewModels
{
    class PersonalStatisticsViewModel : ViewModelBase
    {
        public PersonalStatisticsViewModel()
        {
            this.personalInfo = new PersonalStatistics();
            this.RefreshCmd = new RelayCommand(Refresh);
            Refresh();
        }


        // Fields
        private PersonalStatistics personalInfo;

        // Error message fields
        private string _errorMessage;

        // Properties
        public PersonalStatistics PersonalInfo
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


        // Commands
        public ICommand RefreshCmd { get; }

        public async void Refresh()
        {
            try
            {
                PersonalStatisticsRequest request = new PersonalStatisticsRequest();
                var responseInfo = await RequestsExchangeService.ExchangeRequest(request);

                if (responseInfo.Code == (byte)ResponsesCodes.ErrorResponse)
                {
                    var error = JsonResponseDeserialize.DeserializeResponse<ErrorResponse>(responseInfo);
                    return;
                }

                var personalStatisticsResponse =
                    JsonResponseDeserialize.DeserializeResponse<PersonalStatisticsResponse>(responseInfo);
                this.PersonalInfo = personalStatisticsResponse.Statistics;
            }
            catch (Exception ex)    
            {
                ErrorMessage = $"Error retrieving data on user: {ex.Message}";
            }
        }

    }
}
