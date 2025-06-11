#pragma once
#include "IRequestHandler.hpp"
#include "Room.hpp"
#include "LoggedUser.hpp"
#include "RoomManager.hpp"
#include "RequestHandlerFactory.hpp"
#include "RequestInfo.hpp"
#include "RequestResult.hpp"

class RoomRequestHandler : public IRequestHandler {
public:
	RequestResult getRoomState(const RequestInfo& requestinfo);
	RoomRequestHandler(Room* room, LoggedUser user, RoomManager& roomManager,RequestHandlerFactory& requestHandlerFactory);

protected:
	Room* m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_requestHandlerFactory;
	
private:
	RoomStatus prevStatus;
};