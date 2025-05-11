#include "RoomManager.h"

#include "MyException.h"

unsigned int RoomManager::ids = 0;

RoomManager& RoomManager::getInstance(IDatabase& database)
{
    static RoomManager instance(database); 
    return instance;
}

unsigned int RoomManager::getTotalQuestionsCount() const
{
    return this->m_database.getQuestionsCount();
}

RoomManager::RoomManager(IDatabase& database) : m_database(database)
{
   this->m_rooms = std::map<int, Room>();
}
RoomManager::~RoomManager()
{

}


unsigned int RoomManager::createRoom(const LoggedUser& player, RoomData& roomData)
{
    int roomid = ids++;
    roomData.id = roomid;
    for (const auto& pair : this->m_rooms)
    {
        if (pair.first >= roomid) {
            roomid = pair.first + 1;
        }

    }

    this->m_rooms[roomid] = Room(roomData, player);
    return roomid;
}

void RoomManager::deleteRoom(int ID)
{
    this->m_rooms.erase(this->m_rooms.find(ID));
}

bool RoomManager::getRoomState(int ID)
{
    auto it = this->m_rooms.find(ID);
    if (it != this->m_rooms.end())
    {
        return it->second.getRoomStatus(); 
    }
    return false;
}

std::vector<RoomPreview> RoomManager::getRooms() const
{
	std::vector<RoomPreview> roomsvec;
	for (auto& room : this->m_rooms) 
	{
		roomsvec.push_back(room.second.getRoomPreview());
	}
    return roomsvec;
}

Room& RoomManager::getRoom(int ID)
{
    auto it = this->m_rooms.find(ID);
    if (it != this->m_rooms.end())
    {
        return it->second;
    }
    throw MyException("Room not exist");
}