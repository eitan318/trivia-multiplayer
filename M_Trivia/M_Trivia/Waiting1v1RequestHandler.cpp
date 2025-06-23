#include "Waiting1v1RequestHandler.hpp"
#include "RequestsCodes.hpp"
#include "JsonResponsePacketSerializer.hpp"
#include "JsonRequestPacketDeserializer.hpp"
#include "GeneralResponseErrors.hpp"
#include "Response.hpp"

Waiting1v1RequestHandler::Waiting1v1RequestHandler( RequestHandlerFactory& handlerFactory, const LoggedUser& user) :
	m_handlerFactory(handlerFactory), m_waiting1v1Manager(handlerFactory.getWaiting1v1Manager()), m_user(user) {
}

Waiting1v1RequestHandler::~Waiting1v1RequestHandler()
{

}

bool Waiting1v1RequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
	switch (static_cast<RequestCodes>(requestInfo.code)) {
	case RequestCodes::Leave1v1WaitingListRequest:
	case RequestCodes::DidFound1v1MatchRequest:
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
	case RequestCodes::DidFound1v1MatchRequest:
		return didFoundMatch(requestInfo);
	default:
		ServerErrorResponse errorResponse(GENERAL_SUCCESS_RESPONSE_STATUS, "Invalid msg code.");
		RequestResult requestResult(
			JsonResponsePacketSerializer::serializeResponse(errorResponse),
			nullptr);
		return requestResult;
	}
}

void Waiting1v1RequestHandler::Cleanup()
{
	this->m_waiting1v1Manager.leaveWaitingList(this->m_user);
	this->m_handlerFactory.getLoginManager().logout(this->m_user);
}

RequestResult Waiting1v1RequestHandler::leave1v1WaitingRoom(const RequestInfo& requestInfo)
{
	GeneralResponseErrors errors = this->m_waiting1v1Manager.leaveWaitingList(this->m_user);
	Leave1v1WaitingListResponse response(std::make_unique<GeneralResponseErrors>(errors));
	return RequestResult(
		JsonResponsePacketSerializer::serializeResponse(response),
		errors.statusCode() == 0 ? this->m_handlerFactory.createMenuRequestHandler(this->m_user) : nullptr);
}

RequestResult Waiting1v1RequestHandler::didFoundMatch(const RequestInfo& requestInfo)
{
	 auto [errors, game] = this->m_waiting1v1Manager.didPlayerFoundMatch(this->m_user);
	 bool didFoundMatch = game != nullptr;

	DidFound1v1MatchResponse response(std::make_unique<GeneralResponseErrors>(errors), didFoundMatch);

	std::shared_ptr<IRequestHandler> nextHandler = didFoundMatch ?
		m_handlerFactory.createGameRequestHandler(this->m_user, game, this->m_waiting1v1Manager.getGameRoomPreview(), 
			this->shared_from_this()) : nullptr;

	return RequestResult(
		JsonResponsePacketSerializer::serializeResponse(response),
		nextHandler
		);
}

