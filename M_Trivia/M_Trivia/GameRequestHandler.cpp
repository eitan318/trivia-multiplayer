#include "GameRequestHandler.hpp"
#include "JsonResponsePacketSerializer.hpp"
#include "JsonRequestPacketDeserializer.hpp"
#include "RequestsCodes.hpp"
#include "GetQuestionResponseData.hpp"
#include "Response.hpp"
#include "Requests.hpp"

GameRequestHandler::GameRequestHandler(const LoggedUser& user,
    RequestHandlerFactory& handlerFactory, std::shared_ptr<Game> game, std::shared_ptr<RoomPreview> roomPreview, std::shared_ptr<IRequestHandler> prevRequestHandler) :
    m_gameManager(handlerFactory.getGameManager()),
    m_handlerFactory(handlerFactory),
    m_user(user),
    m_game(std::move(game)),
    m_roomPreview(roomPreview),
    m_prevHandler(prevRequestHandler)
{
    this->m_game->join(user);
    if (m_game->countActivePlayers() == m_roomPreview->currPlayersAmount) {
        m_roomPreview->enterGame();
    }
}

GameRequestHandler::~GameRequestHandler() = default;

bool GameRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const 
{
    switch (static_cast<RequestCodes>(requestInfo.code)) {
    case RequestCodes::LeaveGameRequest:
    case RequestCodes::GetQuestionRequest:
    case RequestCodes::SubmitAnswerRequest:
    case RequestCodes::GetGameResultRequest:
    case RequestCodes::GetGameStateRequest:
        return true;
    default:
        return false;
    }
}

RequestResult GameRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
    switch (static_cast<RequestCodes>(requestInfo.code)) {
    case RequestCodes::LeaveGameRequest:
        return this->leaveGame(requestInfo);
    case RequestCodes::GetQuestionRequest:
        return this->getQuestion(requestInfo);
    case RequestCodes::SubmitAnswerRequest:
        return this->submitAnswer(requestInfo);
    case RequestCodes::GetGameResultRequest:
        return this->getGameResults(requestInfo);
    case RequestCodes::GetGameStateRequest:
        return this->getGameState(requestInfo);
    default:
        ServerErrorResponse errorResponse(GENERAL_SUCCESS_RESPONSE_STATUS, "Invalid msg code.");
        RequestResult requestResult(
            JsonResponsePacketSerializer::serializeResponse(errorResponse),
            nullptr);
    }
}

void GameRequestHandler::Cleanup()
{
    this->m_game->playerDeactivate(this->m_user);
    if (this->m_roomPreview->roomData.id != 0) {
        this->m_handlerFactory.getRoomManger().leaveRoom(this->m_roomPreview->roomData.id, this->m_user);
    }
    this->m_handlerFactory.getLoginManager().logout(this->m_user);
}

RequestResult GameRequestHandler::getQuestion(RequestInfo requestInfo)
{
    GeneralResponseErrors errors;
    std::optional<Question> questionForUserOp = this->m_game->getQuestionForUser(m_user);

    if (!questionForUserOp.has_value()) {
        if (this->m_game->userExistsInGame(m_user)) {
            errors.generalError = "Finished all questions";
        }
        else {
            errors.generalError = "User does not exist in game";
        }
    }
    Question questionForUser = questionForUserOp.has_value() ? questionForUserOp.value() : Question{};
    
    GetQuestionResponse getQuestionResponse(std::make_unique<GeneralResponseErrors>(errors), GetQuestionResponseData{ questionForUser, this->m_game->getCurrQuestionIdx() + 1 });

    RequestResult requestResult(
        JsonResponsePacketSerializer::serializeResponse(getQuestionResponse),
        nullptr);
    return requestResult;
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo requestInfo)
{
    SubmitAnswerRequest request =
        JsonRequestPacketDeserializer::deserializeRequest<SubmitAnswerRequest>(
            requestInfo.buffer);

    int answerId = request.answerId;
    GeneralResponseErrors errors;

    std::optional<Question> currQ = this->m_game->getQuestionForUser(m_user);
    errors = this->m_gameManager.submitAnswer(this->m_user, this->m_game, answerId);


    SubmitAnswerResponse submitAnswerResponse(std::make_unique<GeneralResponseErrors>(errors), currQ.value().getCorrectAnswerId());

    RequestResult requestResult(
        JsonResponsePacketSerializer::serializeResponse(submitAnswerResponse),
        nullptr);
    return requestResult;
}

RequestResult GameRequestHandler::getGameResults(RequestInfo requestInfo)
{
    std::vector<PlayerResults> playersResults = this->m_gameManager.getGameResults(this->m_game);

    GetGameResultsResponse getGameResults(GENERAL_SUCCESS_RESPONSE_STATUS, playersResults);

    RequestResult requestResult(
        JsonResponsePacketSerializer::serializeResponse(getGameResults),
        nullptr);
    return requestResult;
}

RequestResult GameRequestHandler::getGameState(RequestInfo requestInfo)
{
    GetGameStateResponse getGameState(GENERAL_SUCCESS_RESPONSE_STATUS, this->m_game->getStatus());

    RequestResult requestResult(
        JsonResponsePacketSerializer::serializeResponse(getGameState),
        nullptr);
    return requestResult;
}

RequestResult GameRequestHandler::leaveGame(RequestInfo requestInfo)
{
    GeneralResponseErrors errors;
    LeaveGameResponse leaveGameResponse(std::make_unique<GeneralResponseErrors>(errors));
    std::shared_ptr<Room> room = this->m_handlerFactory.getRoomManger().getRoom(this->m_roomPreview->roomData.id);
    std::shared_ptr<IRequestHandler> nextHandler = m_prevHandler;

    this->m_gameManager.leaveGame(this->m_game, this->m_roomPreview, this->m_user);


    RequestResult requestResult(
        JsonResponsePacketSerializer::serializeResponse(leaveGameResponse),
        nextHandler);
    return requestResult;
}