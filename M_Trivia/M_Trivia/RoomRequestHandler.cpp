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
    if (this->m_room->getRoomPreview().gameStarted()) {
        std::shared_ptr<Game> game = this->m_handlerFactory.getGameManager().getGame(m_room->getId());
        nextHandler = this->m_handlerFactory.createGameRequestHandler(m_user, game, m_room->getRoomPreview());
    }

    GetRoomStateResponse roomStateResponse((unsigned int)GENERAL_SUCCESS_RESPONSE_STATUS, state);

    RequestResult requestResult(
        JsonResponsePacketSerializer::serializeResponse(roomStateResponse),
        nextHandler);
    return requestResult;
}

RequestResult RoomRequestHandler::leaveRoom(RequestInfo requestInfo)
{
	this->m_roomManager.leaveRoom(this->m_room->getId(), this->m_user);
	LeaveRoomResponse leaveRoomResponse(GENERAL_SUCCESS_RESPONSE_STATUS);
	RequestResult result;
	result.response = JsonResponsePacketSerializer::serializeResponse(leaveRoomResponse);
	result.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user);
	return result;
}

void RoomRequestHandler::Cleanup()
{
	this->m_handlerFactory.getRoomManger().leaveRoom(this->m_room->getId(), this->m_user);
	this->m_handlerFactory.getLoginManager().logout(this->m_user);
}


RequestResult RoomRequestHandler::handleRequest(const RequestInfo& requestInfo) {
	switch (static_cast<RequestCodes>(requestInfo.code)) {
	case RequestCodes::GetRoomStateRequest:
		return this->getRoomState(requestInfo);
    case RequestCodes::LeaveRoomRequest:
		return this->leaveRoom(requestInfo);
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
	case RequestCodes::LeaveRoomRequest:
        return true;
    default:
        return false;
    }
}

RoomRequestHandler::RoomRequestHandler(RequestHandlerFactory& requestHandlerFactory, LoggedUser user, unsigned int roomId)
	: m_user(user),
	m_room(m_handlerFactory.getRoomManger().getRoom(roomId)),
	m_roomManager(m_handlerFactory.getRoomManger()),
	m_handlerFactory(requestHandlerFactory)  
{}