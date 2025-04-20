#pragma once
#pragma once
#include "LoggedUser.h"
#include "Requests.hpp"
#include "RequestHandlerFactory.h"
#include "JoinRoomResponseStatus.h"

class MenuRequestHandler : public IRequestHandler {
private:
	LoggedUser& m_user;
	RequestHandlerFactory& m_handlerFactory;
	RequestResult signout(const RequestInfo& requestInfo);
	RequestResult getRooms(const RequestInfo& requestInfo);
	RequestResult getPlayersInRoom(const RequestInfo& requestInfo);
	RequestResult getPersonalStats(const RequestInfo& requestInfo);
	RequestResult getHighScore(const RequestInfo& requestInfo);
	RequestResult joinRoom(const RequestInfo& requestInfo);
	RequestResult createRoom(const RequestInfo& requestInfo);
public:
	MenuRequestHandler(LoggedUser& user, RequestHandlerFactory& handlerFactory);
	bool isRequestRelevant(const RequestInfo& requestInfo) const;
	RequestResult handleRequest(const RequestInfo& requestInfo);
};