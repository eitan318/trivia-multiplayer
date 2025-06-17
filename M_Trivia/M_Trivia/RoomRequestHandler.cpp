#include "RoomRequestHandler.hpp"
#include "JsonResponsePacketSerializer.hpp"
#include "GetRoomStateResponse.hpp"
#include "RoomState.hpp"
#include "RoomData.hpp"
#include "RoomStatus.h"
#include "RequestsCodes.hpp"
#include "ServerErrorResponse.hpp"

RequestResult RoomRequestHandler::getRoomState(const RequestInfo& requestinfo)
{
    RoomState state = this->m_room->getRoomState();
    std::shared_ptr<IRequestHandler> nextHandler = nullptr;
    if (this->m_room->gameStarted()) {
        std::shared_ptr<Game> game = this->m_requestHandlerFactory.getGameManager().getGame(m_room->getId());
        nextHandler = this->m_requestHandlerFactory.createGameRequestHandler(m_user, game, m_room);
    }

    GetRoomStateResponse roomStateResponse((unsigned int)GENERAL_SUCCESS_RESPONSE_STATUS, state);

    RequestResult requestResult(
        JsonResponsePacketSerializer::serializeResponse(roomStateResponse),
        nextHandler);
    return requestResult;
}

RequestResult RoomRequestHandler::handleRequest(const RequestInfo& requestInfo, SOCKET socket) {
	switch (static_cast<RequestCodes>(requestInfo.code)) {
	case RequestCodes::GetRoomStateRequest:
		return this->getRoomState(requestInfo);
	default:
		ServerErrorResponse errorResponse("Invalid msg code.");
		RequestResult requestResult(
			JsonResponsePacketSerializer::serializeResponse(errorResponse),
			nullptr);
		return requestResult;
	}
}

bool RoomRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
    switch (static_cast<RequestCodes>(requestInfo.code)) {
    case RequestCodes::GetRoomStateRequest:
        return true;
    default:
        return false;
    }
}

RoomRequestHandler::RoomRequestHandler(Room* room, LoggedUser user, 
	RequestHandlerFactory& requestHandlerFactory) 
	: m_user(user),m_room(room),
	m_roomManager(m_requestHandlerFactory.getRoomManger()),
	m_requestHandlerFactory(requestHandlerFactory)  
{}