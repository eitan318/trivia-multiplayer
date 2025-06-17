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
	RoomRequestHandler(Room* room, LoggedUser user, RequestHandlerFactory& requestHandlerFactory);

	RequestResult handleRequest(const RequestInfo& requestInfo, SOCKET socket) override;
	bool isRequestRelevant(const RequestInfo& requestInfo) const override;

protected:
	RequestHandlerFactory& m_requestHandlerFactory;
	Room* m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
};