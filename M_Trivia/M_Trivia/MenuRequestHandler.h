#pragma once
#include "LoggedUser.h"
#include "Requests.hpp"
#include "RequestHandlerFactory.h"
#include "JoinRoomResponseStatus.h"
#include "CreateRoomResponseStatus.h"
#include "Responses.hpp"

class RequestHandlerFactory;


class MenuRequestHandler : public IRequestHandler {
private:
	LoggedUser& m_user;
	RequestHandlerFactory& m_handlerFactory;
	RequestResult signout(const RequestInfo& requestInfo) const;
	RequestResult getRooms(const RequestInfo& requestInfo) const;
	RequestResult getPlayersInRoom(const RequestInfo& requestInfo) const;
	RequestResult getPersonalStats(const RequestInfo& requestInfo) const;
	RequestResult getHighScore(const RequestInfo& requestInfo) const;
	RequestResult joinRoom(const RequestInfo& requestInfo) const;
	RequestResult createRoom(const RequestInfo& requestInfo) const;
public:
	MenuRequestHandler(LoggedUser& user, RequestHandlerFactory& handlerFactory);
	bool isRequestRelevant(const RequestInfo& requestInfo) const;
	RequestResult handleRequest(const RequestInfo& requestInfo) const;
};