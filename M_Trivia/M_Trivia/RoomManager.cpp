#include "RoomManager.hpp"
#include "CreateRoomResponseErrors.hpp"
#include "JoinRoomResponseErrors.hpp"
#include "LoggedUser.hpp"
#include "MyException.hpp"
#include "Response.hpp"
#include <mutex>


unsigned int RoomManager::ids = 0;

RoomManager& RoomManager::getInstance(IDatabase& database) {
    static RoomManager instance(database);
    return instance;
}

RoomManager::~RoomManager() {}


RoomManager::RoomManager(IDatabase& database) : m_database(database) {
    this->m_rooms = std::vector<Room>();
}

CreateRoomResponseErrors RoomManager::createRoom(const LoggedUser& player,
    RoomData& roomData) {

    CreateRoomResponseErrors createRoonResponseErrors;
    unsigned int totalQuestionCount;

    totalQuestionCount = this->m_database.getQuestionsCount();

    if (roomData.numOfQuestionsInGame > totalQuestionCount) {
        createRoonResponseErrors.questionCountError =
            "Too many questions, there are only: " +
            std::to_string(totalQuestionCount);
    }

    if (createRoonResponseErrors.statusCode() == 0) {
        std::lock_guard<std::mutex> lock(this->m_roomsMutex);
        int roomid = ids++;
        roomData.id = roomid;
        this->m_rooms.emplace_back(roomData, player);
    }
    return createRoonResponseErrors;
}


void RoomManager::deleteRoom(int ID) {
    std::lock_guard<std::mutex> lock(this->m_roomsMutex);
    auto it = std::find_if(m_rooms.begin(), m_rooms.end(), [ID](const Room& room) {
        return room.getRoomPreview().roomData.id == ID;
        });
    if (it != m_rooms.end()) {
        m_rooms.erase(it);
    }
}


std::vector<RoomPreview> RoomManager::getRooms() const {
    std::lock_guard<std::mutex> lock(this->m_roomsMutex);
    std::vector<RoomPreview> roomsvec;
    for (const auto& room : m_rooms) {
        roomsvec.push_back(room.getRoomPreview());
    }
    return roomsvec;
}


CloseRoomResponseErrors RoomManager::closeRoom(Room* room)
{
    CloseRoomResponseErrors errors;
    if (room->getRoomStatus() == RoomStatus::Closed) {
        errors.generalError = "Room already closed";
    }

    if (errors.statusCode() == GENERAL_SUCCESS_RESPONSE_STATUS) {
        room->close();
    }
    return errors;
}

StartGameResponseErrors RoomManager::startGameOfRoom(Room* room)
{
    StartGameResponseErrors errors;
    if (room->getRoomStatus() == RoomStatus::Closed) {
        errors.generalError = "Cannot start game of a closed room.";
    }
    else if (room->getRoomStatus() == RoomStatus::InGame) {
        errors.generalError = "Room is already in game.";
    }
    else if (room->getUsersVector().size() < 2) {
        errors.generalError = "Not enougth palyers.";
    }

    if (errors.statusCode() == GENERAL_SUCCESS_RESPONSE_STATUS) {
        room->startGame();
    }
    return errors;
}



JoinRoomResponseErrors RoomManager::joinRoom(unsigned int id,
    const LoggedUser& loggedUser) {

    JoinRoomResponseErrors errors;
    Room* room = this->getRoom(id);
    std::lock_guard<std::mutex> lock(this->m_roomsMutex);
    if (room != nullptr) {
        if (room->hasUser(loggedUser.getUsername())) {
            errors.generalError = "You are already inside this room.";
        }
        else if (room->getRoomPreview().roomData.maxPlayers ==
            room->getUsersVector().size()) {
            errors.generalError = "Room is already full.";
        }
        else if (room->getRoomStatus() == RoomStatus::InGame) {
            errors.generalError = "Room is inGame.";
        }
        else {
            room->addUser(loggedUser);
        }
    }
    else {
        errors.generalError = "room does not exist.";
    }
    return errors;
}



Room* RoomManager::getRoom(int ID) {
    std::lock_guard<std::mutex> lock(this->m_roomsMutex);
    auto it = std::find_if(m_rooms.begin(), m_rooms.end(), [ID](const Room& room) {
        return room.getRoomPreview().roomData.id == ID;
        });
    if (it != m_rooms.end()) {
        return &(*it);
    }
    return nullptr;
}


