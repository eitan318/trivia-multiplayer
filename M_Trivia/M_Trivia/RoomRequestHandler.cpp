#include "RoomRequestHandler.hpp"
#include "JsonResponsePacketSerializer.hpp"
#include "GetRoomStateResponse.hpp"
#include "RoomState.hpp"
#include "RoomData.hpp"
#include "RoomStatus.h"

RequestResult RoomRequestHandler::getRoomState(const RequestInfo& requestinfo)
{
    std::shared_ptr<IRequestHandler> nextHandler = nullptr;
    if (this->m_room->justOpenedGame()) {
        std::shared_ptr<Game> game = this->m_requestHandlerFactory.getGameManager().getGame(m_room->getId());
        nextHandler = this->m_requestHandlerFactory.createGameRequestHandler(m_user, game, m_room);
    }

    GetRoomStateResponse roomStateResponse((unsigned int)GENERAL_SUCCESS_RESPONSE_STATUS, this->m_room->getRoomState());

    RequestResult requestResult(
        JsonResponsePacketSerializer::serializeResponse(roomStateResponse),
        nextHandler);
    return requestResult;
}

RoomRequestHandler::RoomRequestHandler(Room* room, LoggedUser user, 
	RequestHandlerFactory& requestHandlerFactory) 
	: m_user(user),m_room(room),
	m_roomManager(m_requestHandlerFactory.getRoomManger()),
	m_requestHandlerFactory(requestHandlerFactory)  
{}