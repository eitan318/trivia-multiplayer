#include "RoomAdminRequestHandler.hpp"
#include "RequestsCodes.hpp"
#include "ServerErrorResponse.hpp"
#include "JsonResponsePacketSerializer.hpp"
#include "JsonRequestPacketDeserializer.hpp"

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory,
	LoggedUser loggedUser, 
	Room* room) : RoomRequestHandler(handlerFactory,
		loggedUser, 
		room)
{
}

RoomAdminRequestHandler::~RoomAdminRequestHandler()
{
}

bool RoomAdminRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
	if (RoomRequestHandler::isRequestRelevant(requestInfo))
		return true;
	switch (static_cast<RequestCodes>(requestInfo.code)) {
	case RequestCodes::StartGameRequest:
		return true;
	default:
		return false;
	}
}



RequestResult RoomAdminRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	if (RoomRequestHandler::isRequestRelevant(requestInfo))
		return RoomRequestHandler::handleRequest(requestInfo);

	switch (static_cast<RequestCodes>(requestInfo.code)) {
	case RequestCodes::StartGameRequest:
		return startGame(requestInfo);
	default:
		ServerErrorResponse errorResponse("Invalid msg code.");
		RequestResult requestResult(
			JsonResponsePacketSerializer::serializeResponse(errorResponse),
			nullptr);
		return requestResult;
	}
}


RequestResult RoomAdminRequestHandler::startGame(const RequestInfo& requestInfo)
{
	GeneralResponseErrors errors = this->m_roomManager.startGameOfRoom(this->m_room->getId());
	std::shared_ptr<Game> game = this->m_handlerFactory.getGameManager().createGame(this->m_room->getRoomPreview());

	StartGameResponse startGameResponse(std::make_unique<GeneralResponseErrors>(errors));
	RequestResult result;
	result.response = JsonResponsePacketSerializer::serializeResponse(startGameResponse);
	result.newHandler = errors.statusCode() == 0 ? this->m_handlerFactory.createGameRequestHandler(m_user, game, m_room->getRoomPreview()) : nullptr;
	return result;
}
