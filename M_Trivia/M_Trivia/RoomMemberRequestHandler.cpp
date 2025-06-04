#include "RoomMemberRequestHandler.hpp"
#include "LeaveRoomResponse.hpp"
#include "JsonResponsePacketSerializer.hpp"
#include "RequestsCodes.hpp"
#include "ServerErrorResponse.hpp"


RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory,
	LoggedUser loggedUser, Room* room) :
	RoomRequestHandler(room,
		loggedUser,
		handlerFactory.getRoomManger(),
		handlerFactory)
{
}

RoomMemberRequestHandler::~RoomMemberRequestHandler() 
{
}

bool RoomMemberRequestHandler::isRequestRelevant(const RequestInfo & requestInfo) const 
{
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
	try {
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
	catch (const std::exception& e) {
		ServerErrorResponse errResponse(e.what());
		RequestResult res(
			JsonResponsePacketSerializer::serializeResponse(errResponse), nullptr);
		return res;
	}
}

RequestResult RoomMemberRequestHandler::leaveRoomRequest(RequestInfo requestInfo) 
{
	this->m_room->removeUser(this->m_user);
	if (this->m_room->getUsersVector().empty()) {
		this->m_roomManager.deleteRoom(this->m_room->getId());
	}
	LeaveRoomResponse leaveRoomResponse(GENERAL_SUCCESS_RESPONSE_STATUS);
	RequestResult result;
	result.response = JsonResponsePacketSerializer::serializeResponse(leaveRoomResponse);
	result.newHandler = this->m_requestHandlerFactory.createMenuRequestHandler(this->m_user);
	return result;
}

