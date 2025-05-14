#include "Room.hpp"

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
		if (player->getUsername() == loggeduser.getUsername())
		{
			this->m_users.erase(player);
			return;
		}
	}
}
std::vector<LoggedUser> Room::getAllUsers() const
{
	return this->m_users;
}
bool Room::getRoomStatus() const
{
	return true;
}

void Room::setRoomData(const RoomData& roomdata)
{
	this->m_metadata = roomdata;
}


RoomPreview Room::getRoomPreview() const {
	RoomPreview p;
	p.currPlayersAmount = getAllUsers().size();
	p.status = getRoomStatus();
	p.roomData = this->m_metadata;
	return p;
}
