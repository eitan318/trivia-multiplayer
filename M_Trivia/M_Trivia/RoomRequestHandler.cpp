#include "RoomRequestHandler.hpp"
#include "JsonResponsePacketSerializer.hpp"
#include "GetRoomStateResponse.hpp"
#include "RoomState.hpp"
#include "RoomData.hpp"

RequestResult RoomRequestHandler::getRoomState(RequestInfo requestinfo)
{
    RoomData roomData = this->m_room.getRoomPreview().roomData;
    RoomState roomState(this->m_room.getRoomStatus(), this->m_room.getUsersVector(),
        roomData.numOfQuestionsInGame, roomData.timePerQuestion);

    GetRoomStateResponse roomStateResponse((unsigned int)GENERAL_SUCCESS_RESPONSE_STATUS, roomState);

    RequestResult requestResult(
        JsonResponsePacketSerializer::serializeResponse(roomStateResponse),
        nullptr);
    return requestResult;
}
RoomRequestHandler::RoomRequestHandler(Room room, LoggedUser user, 
	RoomManager& roomManager, RequestHandlerFactory& requestHandlerFactory) 
	: m_user(user),m_room(room),
	m_roomManager(roomManager),
	m_requestHandlerFactory(requestHandlerFactory) 
{}