#include "Room.hpp"
#include "Response.hpp"
#include <algorithm>

Room::Room(std::shared_ptr<RoomPreview> metadata)
    : m_metadata(std::move(metadata)), m_users {metadata->admin} {
}

Room::Room(std::shared_ptr<RoomPreview> metadata, const std::vector<LoggedUser>& users)
    : m_metadata(std::move(metadata)), m_users(users) {
}



Room::~Room()
{
}

void Room::addUser(const LoggedUser& loggeduser) {
    if (std::none_of(m_users.begin(), m_users.end(), [&loggeduser](const LoggedUser& u) {
        return u.getUsername() == loggeduser.getUsername();
        })) {
        m_users.push_back(loggeduser);
        this->getRoomPreview()->currPlayersAmount++;
    }
}

void Room::removeUser(const LoggedUser& loggeduser) {
    size_t removedCount = std::erase_if(m_users, [&loggeduser](const LoggedUser& u) {
        return u.getUsername() == loggeduser.getUsername();
        });
    if (removedCount > 0) {
        this->getRoomPreview()->currPlayersAmount--;
    }
}



const std::vector<LoggedUser>& Room::getUsersVector() const {
    return m_users;
}




unsigned int Room::getId() const {
    return this->m_metadata->roomData.id;
}

RoomStatus Room::getRoomStatus() const {
    return this->m_metadata->status;
}

RoomState Room::getRoomState() const
{
    return RoomState(this->m_metadata->status, this->m_users,
        m_metadata->roomData.numOfQuestionsInGame, m_metadata->roomData.timePerQuestion);
}

std::shared_ptr<RoomPreview> Room::getRoomPreview() const {
    return m_metadata;
}

bool Room::hasUser(const LoggedUser& user) const {
    return std::find(m_users.begin(), m_users.end(), user) != m_users.end();
}


bool Room::isAdmin(const LoggedUser& user) const
{
    return this->m_users[0] == user;
}

