#pragma once
#include "Room.h"
#include <map>

class RoomManager {
private:
	std::map<int, Room> m_rooms;
public:
	void createRoom(LoggedUser player, RoomData roomData);
	void deleteRoom(int ID);
	bool getRoomState(int Id);
	std::vector<RoomData> getRooms();
	Room& getRoom(int ID);
};