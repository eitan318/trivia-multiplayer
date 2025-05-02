using ClientApp.Models;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Printing;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
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
            getPersonalStats();
        }
        public static PersonalStatisticsPageViewModel Instance(Page owner)
        {
            return GetInstance(() => new PersonalStatisticsPageViewModel(owner));
        }
        private Page ownerPage;
        private string _errorMessage;
        private List<PersonalStatistics> personalInfoList;
        public List<PersonalStatistics> PersonalInfoList
        {
            get => new List<PersonalStatistics> { personalInfo };
        }

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

        public ICommand getPersonalStatsCommand { get; }

        public async void getPersonalStats()
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
                this.PersonalInfoList.Add(PersonalInfo);
            }
            catch (Exception ex)
            {
                ErrorMessage = $"Error retrieving data on user: {ex.Message}";
            }
        }

    }
}
