#include "Room.h"

Room::Room(RoomData& roomdata, LoggedUser& user) 
{
	this->m_metadata = roomdata;
	this->m_users.push_back(user);
}
Room::~Room() {
}

void Room::addUser(LoggedUser& loggeduser) 
{
	this->m_users.push_back(loggeduser);
}
void Room::removeUser(LoggedUser& loggeduser)
{
	for (auto player = this->m_users.begin(); player != this->m_users.end(); ++player) 
	{
		if (player->m_username == loggeduser.m_username) 
		{
			this->m_users.erase(player);
			return;
		}
	}
}
std::vector<std::string> Room::getAllUsers()
{
	std::vector<std::string> userslist;
	for (const auto user : this->m_users) 
	{
		userslist.push_back(user.m_username);
	}
}
RoomData Room::getRoomData() 
{
	return this->m_metadata;
}
void Room::setRoomData(RoomData& roomdata)
{
	this->m_metadata = roomdata;
}
