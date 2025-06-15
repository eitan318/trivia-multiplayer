#include "Room.hpp"
#include "Response.hpp"
#include <algorithm>

Room::Room(const RoomData& roomdata, const LoggedUser& user) {
    this->m_metadata = roomdata;
    this->m_users = std::vector<LoggedUser>();
    this->m_users.push_back(user);
    this->status = RoomStatus::NotInGame;
}

Room::Room() {}

Room::~Room() {}

void Room::addUser(const LoggedUser& loggeduser) {
    auto it = std::find_if(m_users.begin(), m_users.end(), [&loggeduser](const LoggedUser& u) {
        return u.getUsername() == loggeduser.getUsername();
        });
    if (it == m_users.end()) {
        m_users.push_back(loggeduser);
    }
}

void Room::removeUser(const LoggedUser& loggeduser) {
    auto it = std::find_if(m_users.begin(), m_users.end(), [&loggeduser](const LoggedUser& u) {
        return u.getUsername() == loggeduser.getUsername();
        });
    if (it != m_users.end()) {
        m_users.erase(it);
    }
}

std::vector<LoggedUser> Room::getUsersVector() const {
    return m_users;
}

void Room::setRoomData(const RoomData& roomdata) {
    this->m_metadata = roomdata;
}

void Room::close() {
    this->status = RoomStatus::Closed;
}

void Room::startGame() {
    this->status = RoomStatus::InGame;
}

void Room::closeGame() {
    this->status = RoomStatus::NotInGame;
}

unsigned int Room::getId() const {
    return this->m_metadata.id;
}

RoomStatus Room::getRoomStatus() const {
    return this->status;
}

RoomPreview Room::getRoomPreview() const {
    RoomPreview p;
    p.currPlayersAmount = static_cast<unsigned int>(m_users.size());
    p.status = this->status;
    p.roomData = this->m_metadata;
    return p;
}


bool Room::hasUser(const std::string& username) const {
    auto it = std::find_if(m_users.begin(), m_users.end(), [&username](const LoggedUser& user) {
        return user.getUsername() == username;
        });
    return it != m_users.end();
}

bool Room::isAdmin(const LoggedUser& user) const
{
    return this->m_users[0] == user;
}

