#include "RoomManager.h"

unsigned int RoomManager::ids = 0;

RoomManager& RoomManager::getInstance()
{
    static RoomManager instance; 
    return instance;
}

RoomManager::RoomManager()
{

}
RoomManager::~RoomManager()
{

}


void RoomManager::createRoom(LoggedUser& player, RoomData& roomData)
{
    int roomid = ids++;
    roomData.id = roomid;
    for (const auto& pair : this->m_rooms)
    {
        if (pair.first >= roomid)
            roomid = pair.first + 1;
    }

    this->m_rooms[roomid] = Room(roomData, player);
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
        return it->second.getRoomData().status; 
    }
    return false;
}
std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> roomsvec;
	for (auto& room : this->m_rooms) 
	{
		roomsvec.push_back(room.second.getRoomData());
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