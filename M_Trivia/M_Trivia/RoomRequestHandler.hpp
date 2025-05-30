#pragma once
#include "IRequestHandler.hpp"
#include "Room.hpp"
#include "LoggedUser.hpp"
#include "RoomManager.hpp"
#include "RequestHandlerFactory.hpp"
#include "RequestInfo.hpp"
#include "RequestResult.hpp"

class RoomRequestHandler : IRequestHandler {
public:
	RequestResult getRoomState(RequestInfo requestinfo);
	RoomRequestHandler(Room room,LoggedUser user, RoomManager& roomManager,RequestHandlerFactory& requestHandlerFactory);
private:
	Room m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_requestHandlerFactory;
};