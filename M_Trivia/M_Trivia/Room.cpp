#include "Room.hpp"
#include "Response.hpp"

Room::Room(const RoomData& roomdata, const LoggedUser& user) 
{
	this->m_metadata = roomdata;
	this->m_users = std::map<std::string,LoggedUser>();
	this->m_users.insert({ user.getUsername(),user });
	this->status = RoomStatus::Closed;
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
const std::vector<LoggedUser>& Room::getUsersVector() const
{
	std::vector<LoggedUser> users;
	users.reserve(m_users.size()); // Reserve space for efficiency

	std::transform(m_users.begin(), m_users.end(), std::back_inserter(users),
		[](const auto& pair) { return pair.second; });

	return users;
}

const std::map<std::string, LoggedUser>& Room::getUsersMap() const
{
	return this->m_users;
}



void Room::setRoomData(const RoomData& roomdata)
{
	this->m_metadata = roomdata;
}

CloseRoomResponseErrors Room::close()
{
	CloseRoomResponseErrors errors;
	if (this->status == RoomStatus::Closed) {
		errors.generalError = "Room already closed";
	}

	errors.statusCode = !errors.noErrors();
	if (errors.statusCode == GENERAL_SUCCESS_RESPONSE_STATUS) {
		this->status = RoomStatus::Closed;
	}
	return errors;
}

StartGameResponseErrors Room::startGame()
{
	StartGameResponseErrors errors;
	if (this->status == RoomStatus::Closed) {
		errors.generalError = "Cannot start game of a closed room.";
	}
	else if (this->status == RoomStatus::InGame) {
		errors.generalError = "Room is already in game.";
	}

	errors.statusCode = !errors.noErrors();
	if (errors.statusCode == GENERAL_SUCCESS_RESPONSE_STATUS) {
		this->status = RoomStatus::InGame;
	}
	return errors;
}


RoomStatus Room::getRoomStatus()
{
	return this->status;
}


RoomPreview Room::getRoomPreview() const {
	RoomPreview p;
	p.currPlayersAmount = getUsersVector().size();
	p.status =  this->status;
	p.roomData = this->m_metadata;
	return p;
}



