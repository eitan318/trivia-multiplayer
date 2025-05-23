#include "RoomManager.hpp"
#include "CreateRoomResponseErrors.hpp"
#include "JoinRoomResponseErrors.hpp"
#include "LoggedUser.hpp"
#include "MyException.hpp"
#include <mutex>

unsigned int RoomManager::ids = 0;

RoomManager& RoomManager::getInstance(IDatabase& database) {
    static RoomManager instance(database);
    return instance;
}

RoomManager::RoomManager(IDatabase& database) : m_database(database) {
    this->m_rooms = std::map<int, Room>();
}

RoomManager::~RoomManager() {}

CreateRoomResponseErrors RoomManager::createRoom(const LoggedUser& player,
    RoomData& roomData) {
    CreateRoomResponseErrors createRoonResponseErrors;
    unsigned int totalQuestionCount = this->m_database.getQuestionsCount();

    if (roomData.numOfQuestionsInGame > totalQuestionCount)
    {
        createRoonResponseErrors.questionCountError =
            "Too many questions, there are only: " +
            std::to_string(totalQuestionCount);
    }
    createRoonResponseErrors.statusCode = !createRoonResponseErrors.noErrors();

    if (createRoonResponseErrors.statusCode == 0)
    {
        int roomid = ids++;
        roomData.id = roomid;
        std::lock_guard<std::mutex> lock(this->m_roomsMutex);
        this->m_rooms[roomid] = Room(roomData, player);
    }
    return createRoonResponseErrors;
}

void RoomManager::deleteRoom(int ID) {
    std::lock_guard<std::mutex> lock(this->m_roomsMutex);
    auto it = this->m_rooms.find(ID);
    if (it != this->m_rooms.end()) {
        this->m_rooms.erase(it);
    }
}

bool RoomManager::getRoomState(int ID) const {
    std::lock_guard<std::mutex> lock(this->m_roomsMutex);
    auto it = this->m_rooms.find(ID);
    if (it != this->m_rooms.end()) {
        return it->second.getRoomStatus();
    }
    return false;
}


std::vector<RoomPreview> RoomManager::getRooms() const {
    std::vector<RoomPreview> roomsvec;
    for (auto& room : this->m_rooms) {
        roomsvec.push_back(room.second.getRoomPreview());
    }
    return roomsvec;
}

JoinRoomResponseErrors RoomManager::joinRoom(unsigned int id,
    const LoggedUser& loggedUser) {
    JoinRoomResponseErrors errors;
    try {
        Room& room = this->getRoom(id);
        if (room.getRoomPreview().roomData.maxPlayers ==
            room.getAllUsers().size()) {
            errors.generalError = "Room is already full.";
        }
        else {
            room.addUser(loggedUser);
        }
    }
    catch (MyException err) {
        errors.generalError = "room does not exist.";
    }
    errors.statusCode = !errors.noErrors();
    return errors;
}

Room& RoomManager::getRoom(int ID) {
    std::lock_guard<std::mutex> lock(this->m_roomsMutex);
    auto it = this->m_rooms.find(ID);
    if (it != this->m_rooms.end())
    {
        return it->second;
    }
    throw MyException("Room not exist");
}
