#include "RoomRequestHandler.hpp"
#include "JsonRequestPacketDeserializer.hpp"
#include "GetRoomStateResponse.hpp"

RequestResult RoomRequestHandler::getRoomState(RequestInfo requestinfo)
{
    GetRoomStateResponse getRoomStateResponse;


    RequestResult requestResult(
        JsonResponsePacketSerializer::serializeResponse(logOutResponse),
        this->m_handlerFactory.createLoginRequestHandler());
    return requestResult;
}
RoomRequestHandler::RoomRequestHandler(Room room, LoggedUser user, 
	RoomManager& roomManager, RequestHandlerFactory& requestHandlerFactory) 
	: m_user(user),m_room(room),
	m_roomManager(roomManager),
	m_requestHandlerFactory(requestHandlerFactory) 
{}