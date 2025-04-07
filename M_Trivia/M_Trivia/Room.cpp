#include "Room.h"

void Room::addUser(LoggedUser& loggeduser) 
{
	this->m_users.push_back(loggeduser);
}
void Room::removeUser(LoggedUser& loggeduser)
{
	for (auto player = this->m_users.begin(); player != this->m_users.end(); ++player) {
		if (player->m_username == loggeduser.m_username) {
			this->m_users.erase(player);
			return;
		}
	}
}
std::vector<std::string> Room::getAllUsers()
{

}