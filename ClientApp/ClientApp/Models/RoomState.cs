using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models
{
    public class RoomState
    {
        bool m_hasGameBegun {  get; set; }
        List<LoggedUser> m_players {  get; set; }
        uint m_answerCount {  get; set; }
        double m_answerTimeOut {  get; set; }
    };

}
