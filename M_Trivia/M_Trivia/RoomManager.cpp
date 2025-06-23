#include "RoomManager.hpp"
#include "LoggedUser.hpp"
#include "MyException.hpp"
#include "Response.hpp"
#include <algorithm>
#include <ranges> 


unsigned int RoomManager::ids = 0;

RoomManager& RoomManager::getInstance(IDatabase& database) {
    static RoomManager instance(database);
    return instance;
}

RoomManager::~RoomManager() {}


RoomManager::RoomManager(IDatabase& database) : m_database(database) {
    this->m_rooms = std::vector<Room>();
}

GeneralResponseErrors RoomManager::createRoom(const LoggedUser& player,
    RoomData& roomData) {

    GeneralResponseErrors createRoonResponseErrors;
    unsigned int totalQuestionCount;

    totalQuestionCount = this->m_database.getQuestionsCount();

    if (roomData.numOfQuestionsInGame > totalQuestionCount) {
        createRoonResponseErrors.generalError =
            "Too many questions, there are only: " +
            std::to_string(totalQuestionCount);
    }

    if (createRoonResponseErrors.statusCode() == 0) {
        std::lock_guard<std::mutex> lock(this->m_roomsMutex);
        int roomid = ids++;
        roomData.id = roomid;
        this->m_rooms.emplace_back(std::make_shared<RoomPreview>(roomData, 1, RoomStatus::NotInGame, player));
    }
    return createRoonResponseErrors;
}



void RoomManager::deleteRoom(int ID) {
    std::lock_guard<std::mutex> lock(this->m_roomsMutex);
    std::erase_if(m_rooms, [ID](const Room& room) {
        return room.getRoomPreview()->roomData.id == ID;
        });
}



std::vector<RoomPreview> RoomManager::getActiveRooms() const {
    std::lock_guard<std::mutex> lock(this->m_roomsMutex);
    std::vector<RoomPreview> roomsvec;
    for (const auto& room : m_rooms) {
        if (room.getRoomStatus() != RoomStatus::Closing)
        {
            roomsvec.push_back(*room.getRoomPreview());
        }
    }
    return roomsvec;
}

void RoomManager::leaveRoom(unsigned int roomId,
    const LoggedUser& loggedUser) {
    Room* room = this->getRoom(roomId);
    bool isAdmin = room->isAdmin(loggedUser);

    room->removeUser(loggedUser);
    if (room->getUsersVector().empty()) {
        this->deleteRoom(room->getId());
    }
    else {
        if (isAdmin) {
            room->getRoomPreview()->close();
        }
    }

}


GeneralResponseErrors RoomManager::startGameOfRoom(unsigned int roomId)
{
    Room* room = getRoom(roomId);
    //std::lock_guard<std::mutex> lock(this->m_roomsMutex);
    GeneralResponseErrors errors;
    RoomStatus s = room->getRoomStatus();
    if (s == RoomStatus::Closing) {
        errors.generalError = "Cannot start game of a closed room.";
    }
    else if (s == RoomStatus::InGame || s == RoomStatus::StartingGame) {
        errors.generalError = "Room is already in game.";
    }
    else if (room->getUsersVector().size() < 2) {
        errors.generalError = "Not enougth palyers.";
    }

    if (errors.statusCode() == GENERAL_SUCCESS_RESPONSE_STATUS) {
        room->getRoomPreview()->startGame();
    }
    return errors;
}



GeneralResponseErrors RoomManager::joinRoom(unsigned int id,
    const LoggedUser& loggedUser) {

    GeneralResponseErrors errors;
    Room* room = this->getRoom(id);
    std::lock_guard<std::mutex> lock(this->m_roomsMutex);
    if (room != nullptr) {
        if (room->hasUser(loggedUser)) {
            errors.generalError = "You are already inside this room.";
        }
        else if (room->getRoomPreview()->roomData.maxPlayers ==
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

    auto it = std::ranges::find_if(m_rooms, [ID](const Room& room) {
        return room.getRoomPreview()->roomData.id == ID;
        });

    return it != m_rooms.end() ? &(*it) : nullptr;
}
