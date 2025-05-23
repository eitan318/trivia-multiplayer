#include "Room.hpp"

Room::Room(const RoomData& roomdata, const LoggedUser& user) 
{
	this->m_metadata = roomdata;
	this->m_users = std::map<std::string,LoggedUser>();
	this->m_users.insert({ user.getUsername(),user });
}
Room::Room() {
}
Room::~Room() {
}

void Room::addUser(const LoggedUser& loggeduser)
{
	this->m_users.insert({ loggeduser.getUsername(), loggeduser });
}

void Room::removeUser(const LoggedUser& loggeduser)
{
	for (auto player = this->m_users.begin(); player != this->m_users.end(); ++player) 
	{
		if (player->first == loggeduser.getUsername())
		{
			this->m_users.erase(player);
			return;
		}
	}
}
std::vector<LoggedUser> Room::getAllUsers() const
{
	std::vector<LoggedUser> users;
	users.reserve(m_users.size()); // Reserve space for efficiency

	std::transform(m_users.begin(), m_users.end(), std::back_inserter(users),
		[](const auto& pair) { return pair.second; });

	return users;
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
