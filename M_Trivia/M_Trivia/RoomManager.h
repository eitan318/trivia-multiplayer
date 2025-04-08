#pragma once
#include "Room.h"
#include <map>

class RoomManager {
private:
	std::map<int, Room> m_rooms;
	RoomManager();
	~RoomManager();
	RoomManager(const RoomManager&) = delete;
	RoomManager& operator=(const RoomManager&) = delete;

public:
	static RoomManager& getInstance();
	void createRoom(LoggedUser& player, RoomData& roomData);
	void deleteRoom(int ID);
	bool getRoomState(int ID);
	std::vector<RoomData> getRooms();
	Room& getRoom(int ID);
};