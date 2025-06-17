#include "RoomMemberRequestHandler.hpp"
#include "JsonResponsePacketSerializer.hpp"
#include "RequestsCodes.hpp"
#include "ServerErrorResponse.hpp"


RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory,
	LoggedUser loggedUser, Room* room) :
	RoomRequestHandler(room,
		loggedUser,
		handlerFactory)
{
}

RoomMemberRequestHandler::~RoomMemberRequestHandler() 
{
}

bool RoomMemberRequestHandler::isRequestRelevant(const RequestInfo & requestInfo) const 
{
	if (RoomRequestHandler::isRequestRelevant(requestInfo))
		return true;

	switch (static_cast<RequestCodes>(requestInfo.code)) {
	case RequestCodes::LeaveRoomRequest:
	case RequestCodes::GetRoomStateRequest:
		return true;
	default:
		return false;
	}
}

RequestResult RoomMemberRequestHandler::handleRequest(const RequestInfo& requestInfo, SOCKET socket)
{
	if (RoomRequestHandler::isRequestRelevant(requestInfo))
		return RoomRequestHandler::handleRequest(requestInfo, socket);

	switch (static_cast<RequestCodes>(requestInfo.code)) {
	case RequestCodes::LeaveRoomRequest:
		return this->leaveRoomRequest(requestInfo);
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

RequestResult RoomMemberRequestHandler::leaveRoomRequest(RequestInfo requestInfo) 
{
	this->m_roomManager.leaveRoom(this->m_room->getId(), this->m_user);
	LeaveRoomResponse leaveRoomResponse(GENERAL_SUCCESS_RESPONSE_STATUS);
	RequestResult result;
	result.response = JsonResponsePacketSerializer::serializeResponse(leaveRoomResponse);
	result.newHandler = this->m_requestHandlerFactory.createMenuRequestHandler(this->m_user);
	return result;
}

