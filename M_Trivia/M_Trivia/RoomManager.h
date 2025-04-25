#pragma once
#include "Room.h"
#include "MyException.h"
#include "IDatabase.h"
#include <map>

class RoomManager {
private:
	static unsigned int ids;
	std::map<int, Room> m_rooms;
	IDatabase* m_database;
	RoomManager(IDatabase& database);
	~RoomManager();
	RoomManager(const RoomManager&) = delete;
	RoomManager& operator=(const RoomManager&) = delete;

public:
	static RoomManager& getInstance(IDatabase& database);
	unsigned int getTotalQuestionsCount();
	void createRoom(LoggedUser& player, RoomData& roomData);
	void deleteRoom(int ID);
	bool getRoomState(int ID);
	std::vector<RoomData> getRooms();
	Room& getRoom(int ID);
};