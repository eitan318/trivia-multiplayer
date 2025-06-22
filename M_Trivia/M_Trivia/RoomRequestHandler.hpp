#pragma once
#include "IRequestHandler.hpp"
#include "Room.hpp"
#include "LoggedUser.hpp"
#include "RoomManager.hpp"
#include "RequestHandlerFactory.hpp"
#include "RequestInfo.hpp"
#include "RequestResult.hpp"

class RoomRequestHandler : public IRequestHandler , public std::enable_shared_from_this<RoomRequestHandler> {
public:
	RoomRequestHandler(RequestHandlerFactory& requestHandlerFactory, LoggedUser user, Room* room);
	~RoomRequestHandler();
	RequestResult handleRequest(const RequestInfo& requestInfo) override;
	bool isRequestRelevant(const RequestInfo& requestInfo) const override;
	void Cleanup() override;

protected:
	RequestResult getRoomState(const RequestInfo& requestinfo);
	RequestResult leaveRoom(RequestInfo requestInfo);

	RequestHandlerFactory& m_handlerFactory;
	Room* m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
};