#include "RoomRequestHandler.hpp"
#include "JsonResponsePacketSerializer.hpp"
#include "GetRoomStateResponse.hpp"
#include "RoomState.hpp"
#include "RoomData.hpp"

RequestResult RoomRequestHandler::getRoomState(const RequestInfo& requestinfo)
{
    GetRoomStateResponse roomStateResponse((unsigned int)GENERAL_SUCCESS_RESPONSE_STATUS, this->m_room->getRoomState());

    RequestResult requestResult(
        JsonResponsePacketSerializer::serializeResponse(roomStateResponse),
        nullptr);
    return requestResult;
}
RoomRequestHandler::RoomRequestHandler(Room* room, LoggedUser user, 
	RequestHandlerFactory& requestHandlerFactory) 
	: m_user(user),m_room(room),
	m_roomManager(m_requestHandlerFactory.getRoomManger()),
	m_requestHandlerFactory(requestHandlerFactory)  
{}