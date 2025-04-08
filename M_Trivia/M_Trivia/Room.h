#pragma once
#include "RoomData.h"
#include "LoggedUser.h"
#include <vector>

class Room {
private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
public:
	Room(RoomData& roomdata, LoggedUser& user);
	Room();
	~Room();
	void addUser(LoggedUser& loggeduser);
	void removeUser(LoggedUser& loggeduser);
	std::vector<std::string> getAllUsers();
	RoomData getRoomData();
	void setRoomData(RoomData& roomdata);
};