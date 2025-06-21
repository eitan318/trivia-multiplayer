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
	RoomRequestHandler(RequestHandlerFactory& requestHandlerFactory, LoggedUser user, unsigned int roomId);

	RequestResult handleRequest(const RequestInfo& requestInfo) override;
	bool isRequestRelevant(const RequestInfo& requestInfo) const override;
	void Cleanup() override;

	RequestResult leaveRoom(RequestInfo requestInfo);
protected:
	RequestHandlerFactory& m_handlerFactory;
	Room* m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
};