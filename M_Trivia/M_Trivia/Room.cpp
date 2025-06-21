#include "Room.hpp"
#include "Response.hpp"
#include <algorithm>

Room::Room(const RoomData& roomdata, const LoggedUser& user)
    : m_metadata(roomdata, (unsigned int)m_users.size(), RoomStatus::NotInGame, user), m_users{user} {
}

Room::Room(const RoomData& roomdata, const std::vector<LoggedUser>& users)
    : m_metadata(roomdata, (unsigned int)m_users.size(), RoomStatus::NotInGame, users[0]), m_users(users)
    {
}


Room::~Room()
{
}

void Room::addUser(const LoggedUser& loggeduser) {
    if (std::none_of(m_users.begin(), m_users.end(), [&loggeduser](const LoggedUser& u) {
        return u.getUsername() == loggeduser.getUsername();
        })) {
        m_users.push_back(loggeduser);
    }
}

void Room::removeUser(const LoggedUser& loggeduser) {
    std::erase_if(m_users, [&loggeduser](const LoggedUser& u) {
        return u.getUsername() == loggeduser.getUsername();
        });
}


const std::vector<LoggedUser>& Room::getUsersVector() const {
    return m_users;
}

void Room::setRoomData(const RoomData& roomdata) {
    this->m_metadata.roomData = roomdata;
}



unsigned int Room::getId() const {
    return this->m_metadata.roomData.id;
}

RoomStatus Room::getRoomStatus() const {
    return this->m_metadata.status;
}

RoomState Room::getRoomState() const
{
    return RoomState(this->m_metadata.status, this->m_users,
        m_metadata.roomData.numOfQuestionsInGame, m_metadata.roomData.timePerQuestion);
}

RoomPreview& Room::getRoomPreview() const {
    return m_metadata;
}

bool Room::hasUser(const LoggedUser& user) const {
    return std::find(m_users.begin(), m_users.end(), user) != m_users.end();
}


bool Room::isAdmin(const LoggedUser& user) const
{
    return this->m_users[0] == user;
}

