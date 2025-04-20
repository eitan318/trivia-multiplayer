using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Responses
{
    enum ResponsesCodes
    {
        ErrorResponse = 0,
        NoDataResponse = 1,
        GetRoomsResponse = 2,
        GetPlayersInRoomResponse = 3,
        GetHighScoreResponse = 4,
        GetPersonalStatsResponse = 5,
        SendPasswordResetCodeResponse = 6,

    }
}
