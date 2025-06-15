#include "RoomAdminRequestHandler.hpp"
#include "RequestsCodes.hpp"
#include "ServerErrorResponse.hpp"
#include "JsonResponsePacketSerializer.hpp"
#include "JsonRequestPacketDeserializer.hpp"
#include "CloseRoomResponse.hpp"
#include "StartGameResponse.hpp"
#include "GetRoomStateResponse.hpp"

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory,
	LoggedUser loggedUser, 
	Room* room) : RoomRequestHandler(room, 
		loggedUser, 
		handlerFactory)
{
}

RoomAdminRequestHandler::~RoomAdminRequestHandler()
{
}

bool RoomAdminRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
	switch (static_cast<RequestCodes>(requestInfo.code)) {
	case RequestCodes::CloseRoomRequest:
	case RequestCodes::StartGameRequest:
	case RequestCodes::GetRoomStateRequest:
		return true;
	default:
		return false;
	}
}
RequestResult RoomAdminRequestHandler::handleRequest(const RequestInfo& requestInfo, SOCKET socket)
{

	try {
		switch (static_cast<RequestCodes>(requestInfo.code)) {
		case RequestCodes::CloseRoomRequest:
			return closeRoom(requestInfo);
		case RequestCodes::StartGameRequest:
			return startGame(requestInfo);
		case RequestCodes::GetRoomStateRequest:
			return getRoomState(requestInfo);
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

RequestResult RoomAdminRequestHandler::closeRoom(const RequestInfo& requestInfo)
{
	CloseRoomResponseErrors errors = this->m_roomManager.closeRoom(this->m_room);

	CloseRoomResponse closeRoomResponse(&errors);
	RequestResult result;
	result.response = JsonResponsePacketSerializer::serializeResponse(closeRoomResponse);
	result.newHandler = this->m_requestHandlerFactory.createMenuRequestHandler(this->m_user);
	return result;
}

RequestResult RoomAdminRequestHandler::startGame(const RequestInfo& requestInfo)
{
	StartGameResponseErrors errors = this->m_roomManager.startGameOfRoom(this->m_room);

	StartGameResponse startGameResponse(&errors);
	RequestResult result;
	result.response = JsonResponsePacketSerializer::serializeResponse(startGameResponse);
	result.newHandler = nullptr;
	return result;
}
