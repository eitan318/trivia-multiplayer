#include "RoomRequestHandler.hpp"
#include "JsonResponsePacketSerializer.hpp"
#include "GetRoomStateResponse.hpp"
#include "RoomState.hpp"
#include "RoomData.hpp"
#include "RoomStatus.h"

RequestResult RoomRequestHandler::getRoomState(const RequestInfo& requestinfo)
{
    RoomData roomData = this->m_room->getRoomPreview().roomData;
    RoomState roomState(this->m_room->getRoomStatus(), this->m_room->getUsersVector(),
        roomData.numOfQuestionsInGame, roomData.timePerQuestion);

    GetRoomStateResponse roomStateResponse((unsigned int)GENERAL_SUCCESS_RESPONSE_STATUS, roomState);
    std::shared_ptr<IRequestHandler> nextHandler = nullptr;
    if (prevStatus == RoomStatus::NotInGame && (RoomStatus)roomState.m_roomStatus == RoomStatus::InGame) {
        std::shared_ptr<Game> game = this->m_requestHandlerFactory.getGameManager().getGame(m_room->getId());
        nextHandler = this->m_requestHandlerFactory.createGameRequestHandler(m_user, game, m_room);
    }

    RequestResult requestResult(
        JsonResponsePacketSerializer::serializeResponse(roomStateResponse),
        nextHandler);
    this->prevStatus = (RoomStatus)roomState.m_roomStatus;
    return requestResult;
}
RoomRequestHandler::RoomRequestHandler(Room* room, LoggedUser user, 
	RoomManager& roomManager, RequestHandlerFactory& requestHandlerFactory) 
	: m_user(user),m_room(room),
	m_roomManager(roomManager),
	m_requestHandlerFactory(requestHandlerFactory) 
{}