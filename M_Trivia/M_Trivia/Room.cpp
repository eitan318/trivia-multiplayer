#include "Room.hpp"
#include "Response.hpp"
#include <algorithm>

Room::Room(const RoomData& roomdata, const LoggedUser& user)
    : m_metadata(roomdata), m_users{ user }, status(RoomStatus::NotInGame) {
}

Room::Room() : m_metadata{}, status(RoomStatus::NotInGame) {}

void Room::addUser(const LoggedUser& loggeduser) {
    if (std::none_of(m_users.begin(), m_users.end(), [&loggeduser](const LoggedUser& u) {
        return u.getUsername() == loggeduser.getUsername();
        })) {
        m_users.push_back(loggeduser);
    }
}

void Room::removeUser(const LoggedUser& loggeduser) {
    auto it = std::remove(m_users.begin(), m_users.end(), loggeduser);
    m_users.erase(it, m_users.end());
}

const std::vector<LoggedUser>& Room::getUsersVector() const {
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

unsigned int Room::getId() const {
    return this->m_metadata.id;
}

RoomStatus Room::getRoomStatus() const {
    return this->status;
}

RoomState Room::getRoomState() const
{
    return RoomState(this->status, this->m_users,
        m_metadata.numOfQuestionsInGame, m_metadata.timePerQuestion);
}

RoomPreview Room::getRoomPreview() const {
    return { m_metadata, static_cast<unsigned int>(m_users.size()), status };
}

bool Room::hasUser(const LoggedUser& user) const {
    return std::find(m_users.begin(), m_users.end(), user) != m_users.end();
}
