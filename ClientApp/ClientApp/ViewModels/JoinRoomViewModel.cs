using ClientApp.Commands;
using ClientApp.Models;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Input;

namespace ClientApp.ViewModels
{
    public class JoinRoomViewModel : BaseViewModel
    {
        private Page ownerPage;
        private List<string> RoomNames
        {
            get => RoomNames;
            set
            {
                RoomNames = value;
                OnPropertyChanged(); // Notifies the UI that the value has changed
            }
        }
        private string _selectedRoom;
        public string SelectedRoom
        {
            get => _selectedRoom;
            set { _selectedRoom = value; OnPropertyChanged(); }
        }
        private List<RoomData> Rooms
        {  get; set; }

        private JoinRoomViewModel(Page owner)
        {
            this.ownerPage = owner;
        }
        public static JoinRoomViewModel Instance(Page owner)
        {
            return GetInstance(() => new JoinRoomViewModel(owner));
        }
        public ICommand UpdateCBCommand { get; }
        public ICommand RefreshCommand { get; }
        public ICommand JoinCommand { get; }


        public void updateList()
        {
            //GetRoomsRequest roomsRequest = new GetRoomsRequest();
            //roomsRequest.GetCode();
            GetRoomResponse roomResponse = new GetRoomResponse();
            this.Rooms = roomResponse.Rooms;
            RoomNames = Rooms.Select(r => r.name).ToList();

        }
        public void refresh()
        {
            this.updateList();
        }
        public void joinRoom()
        {
            if (string.IsNullOrEmpty(SelectedRoom))
            {
                return;
            }
            RoomData selected = Rooms.FirstOrDefault(r => r.name == SelectedRoom);
            JoinRoomResponse response = new JoinRoomResponse();
            response.RoomId = selected.id;
            
        }
    }
    
}
