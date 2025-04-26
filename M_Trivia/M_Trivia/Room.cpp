#include "Room.h"

Room::Room(const RoomData& roomdata, const LoggedUser& user) 
{
	this->m_metadata = roomdata;
	this->m_users = std::vector<LoggedUser>();
	this->m_users.push_back(user);
}
Room::Room() {
}
Room::~Room() {
}

void Room::addUser(const LoggedUser& loggeduser)
{
	this->m_users.push_back(loggeduser);
}
void Room::removeUser(const LoggedUser& loggeduser)
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
std::vector<std::string> Room::getAllUsers() const
{
	std::vector<std::string> userslist;
	for (const auto user : this->m_users) 
	{
		userslist.push_back(user.m_username);
	}
	return userslist;
}
RoomData Room::getRoomData() const
{
	return this->m_metadata;
}

void Room::setRoomData(const RoomData& roomdata)
{
	this->m_metadata = roomdata;
}
