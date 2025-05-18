using ClientApp.Commands;
using ClientApp.Models;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using System.Windows.Controls;
using System.Windows.Input;

namespace ClientApp.ViewModels
{
    class PersonalStatisticsPageViewModel : BaseViewModel
    {
        public PersonalStatisticsPageViewModel(Page owner)
        {
            this.ownerPage = owner;
            this.personalInfo = new PersonalStatistics();
            this.RefreshCommand = new RelayCommand(Refresh);
            Refresh();
        }
        public static PersonalStatisticsPageViewModel Instance(Page owner)
        {
            return GetInstance(() => new PersonalStatisticsPageViewModel(owner));
        }
        private Page ownerPage;
        private string _errorMessage;

        private PersonalStatistics personalInfo;
        public PersonalStatistics PersonalInfo
        {
            get => personalInfo;
            set
            {
                personalInfo = value;
                OnPropertyChanged();
            }
        }
        public string ErrorMessage
        {
            get => _errorMessage;
            set
            {
                _errorMessage = value;
                OnPropertyChanged();
            }
        }

        public ICommand RefreshCommand { get; }

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
