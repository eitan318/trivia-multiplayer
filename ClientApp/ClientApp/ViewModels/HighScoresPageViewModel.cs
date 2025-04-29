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

namespace ClientApp.ViewModels
{

    class HighScoresPageViewModel : BaseViewModel
    {
        const int TOP1INDEX = 0;
        const int TOP2INDEX = 1;
        const int TOP3INDEX = 2;
        private HighScoresPageViewModel(Page owner)
        {
            RefreshTop3();
            this.ownerPage = owner;
        }
        public static HighScoresPageViewModel Instance(Page owner)
        {
            return GetInstance(() => new HighScoresPageViewModel(owner));
        }
        /// <summary>
        /// The page that owns this ViewModel. Used for navigation purposes.
        /// </summary>
        private Page ownerPage;
        private string top1Name;
        private string top2Name;
        private string top3Name;
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
        public string Top1Name { get => top1Name; set => top1Name = value; }
        public string Top2Name { get => top2Name; set => top2Name = value; }
        public string Top3Name { get => top3Name; set => top3Name = value; }


        public ICommand BackToStatisticsPageCommand { get; }

        /// <summary>
        /// This function refreshes the top 3 leading players
        /// </summary>
        public async void RefreshTop3()
        { 
            try
            {
                HighScoresRequest request = new HighScoresRequest();
                var responseInfo = await RequestsExchangeService.ExchangeRequest(request);

                if (responseInfo.Code == (byte)ResponsesCodes.ErrorResponse)
                {
                    var error = JsonResponseDeserialize.DeserializeResponse<ErrorResponse>(responseInfo);
                    return;
                }

                var HighestScoresResponse = JsonResponseDeserialize.DeserializeResponse<HighScoresResponse>(responseInfo);
                this.Top1Name = "1st =>" + HighestScoresResponse.HighScores[TOP1INDEX].UserName;
                this.Top2Name = "2nd =>" + HighestScoresResponse.HighScores[TOP2INDEX].UserName;
                this.Top3Name = "3rd =>" + HighestScoresResponse.HighScores[TOP3INDEX].UserName;



            }
            catch (Exception ex)
            {
                ErrorMessage = $"Error retrieving top 3 users: {ex.Message}";
            }
        }

    }
}
