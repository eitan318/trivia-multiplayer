#include "Waiting1v1RequestHandler.hpp"
#include "RequestsCodes.hpp"
#include "JsonResponsePacketSerializer.hpp"
#include "JsonRequestPacketDeserializer.hpp"
#include "GeneralResponseErrors.hpp"
#include "Response.hpp"

Waiting1v1RequestHandler::Waiting1v1RequestHandler(const LoggedUser& user, RequestHandlerFactory& handlerFactory) :
	m_handlerFactory(handlerFactory), m_waiting1v1Manager(handlerFactory.getWaiting1v1Manager()), m_user(user) {


	this->m_waiting1v1Manager.joinWaitingList(m_user);
}

Waiting1v1RequestHandler::~Waiting1v1RequestHandler()
{
}

bool Waiting1v1RequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
	switch (static_cast<RequestCodes>(requestInfo.code)) {
	case RequestCodes::StartGameRequest:
		return true;
	default:
		return false;
	}
}

RequestResult Waiting1v1RequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	switch (static_cast<RequestCodes>(requestInfo.code)) {
	case RequestCodes::Leave1v1WaitingListRequest:
		return leave1v1WaitingRoom(requestInfo);
	default:
		ServerErrorResponse errorResponse(GENERAL_SUCCESS_RESPONSE_STATUS, "Invalid msg code.");
		RequestResult requestResult(
			JsonResponsePacketSerializer::serializeResponse(errorResponse),
			nullptr);
		return requestResult;
	}
}

RequestResult Waiting1v1RequestHandler::leave1v1WaitingRoom(const RequestInfo& requestInfo)
{
	GeneralResponseErrors errors = this->m_waiting1v1Manager.leaveWaitingList(this->m_user);
	Leave1v1WaitingListResponse response(std::make_unique<GeneralResponseErrors>(errors));
	return RequestResult(
		JsonResponsePacketSerializer::serializeResponse(response),
		this->m_handlerFactory.createMenuRequestHandler(this->m_user));
}

RequestResult Waiting1v1RequestHandler::didFoundMatch(const RequestInfo& requestInfo)
{
	auto [errors, didFoundMatch] = this->m_waiting1v1Manager.didPlayerFoundMatch(this->m_user);

	// Construct the response object with the result
	DidFound1v1MatchResponse response(std::make_unique<GeneralResponseErrors>(errors), didFoundMatch);

	std::shared_ptr<RoomPreview> gameRoomPreview = std::make_shared<RoomPreview>(
		RoomData{ 0,"1v1", 2, 10, 5, 2 },
		0,
		RoomStatus::NotInGame,
		LoggedUser{ "no" }
	);

	std::shared_ptr<Game> game = this->m_handlerFactory.getGameManager().createGame(gameRoomPreview);

	std::shared_ptr<IRequestHandler> nextHandler = didFoundMatch ?
		m_handlerFactory.createGameRequestHandler(this->m_user, game, gameRoomPreview) : nullptr;

	// Return the result with the appropriate response
	return RequestResult(
		JsonResponsePacketSerializer::serializeResponse(response),
		nextHandler
		); // Assuming RequestResult accepts a response object
}

