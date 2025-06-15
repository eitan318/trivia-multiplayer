#include "GameRequestHandler.hpp"
#include "RequestsCodes.hpp"
#include "ServerErrorResponse.hpp"
#include "JsonResponsePacketSerializer.hpp"
#include "JsonRequestPacketDeserializer.hpp"
#include "GetGameResultsResponse.hpp"
#include "SubmitAnswerResponse.hpp"
#include "LeaveGameResponse.hpp"
#include "GetQuestionResponse.hpp"
#include "SubmitAnswerRequest.hpp"

GameRequestHandler::GameRequestHandler(const LoggedUser& user,
    RequestHandlerFactory& handlerFactory, std::shared_ptr<Game> game, Room* room) :
    m_gameManager(handlerFactory.getGameManager()),
    m_handlerFactory(handlerFactory),
    m_user(user),
    m_game(std::move(game)),
    m_room(room)
{
}

GameRequestHandler::~GameRequestHandler() = default;

bool GameRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const 
{
    switch (static_cast<RequestCodes>(requestInfo.code)) {
    case RequestCodes::LeaveGameRequest:
    case RequestCodes::GetQuestionRequest:
    case RequestCodes::SubmitAnswerRequest:
    case RequestCodes::GetGameResultRequest:
        return true;
    default:
        return false;
    }
}

RequestResult GameRequestHandler::handleRequest(const RequestInfo& requestInfo, SOCKET socket)
{
    try {
        switch (static_cast<RequestCodes>(requestInfo.code)) {
        case RequestCodes::LeaveGameRequest:
            return this->leaveGame(requestInfo);
        case RequestCodes::GetQuestionRequest:
            return this->getQuestion(requestInfo);
        case RequestCodes::SubmitAnswerRequest:
            return this->submitAnswer(requestInfo);
        case RequestCodes::GetGameResultRequest:
            return this->getGameResults(requestInfo);
        default:
            ServerErrorResponse errorResponse("Invalid msg code.");
            RequestResult requestResult(
                JsonResponsePacketSerializer::serializeResponse(errorResponse),
                nullptr);
        }
    }
    catch (const std::exception& e) {
        ServerErrorResponse errResponse(e.what());
        RequestResult res(
            JsonResponsePacketSerializer::serializeResponse(errResponse), nullptr);
        return res;
    }
}

RequestResult GameRequestHandler::getQuestion(RequestInfo requestInfo)
{
    GeneralResponseErrors errors;
    std::optional<Question> quetionForUser = this->m_game->getQuestionForUser(m_user);
    if (!quetionForUser.has_value()) {
        if (this->m_game->userExistsInGame(m_user)) {
            errors.generalError = "Finished all questions";
        }
        else {
            errors.generalError = "User does not exist in game";
        }
    }

    
    GetQuestionResponse getQuestionResponse(&errors, quetionForUser);

    RequestResult requestResult(
        JsonResponsePacketSerializer::serializeResponse(getQuestionResponse),
        nullptr);
    return requestResult;
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo requestInfo)
{
    SubmitAnswerRequest request =
        JsonRequestPacketDeserializer<SubmitAnswerRequest>::deserializeRequest(
            requestInfo.buffer);

    int answerId = request.getAnswerId();
    int answerScore = 0;
    GeneralResponseErrors errors;
    errors = this->m_gameManager.submitAnswer(this->m_user, this->m_game, answerId, &answerScore);

    std::optional<Question> currQ = this->m_game->getQuestionForUser(m_user);

    this->m_game->setNextQuestionForUser(this->m_user);

    SubmitAnswerResponse submitAnswerResponse(&errors, currQ.value().getCorrectAnswerId(), answerScore);

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

RequestResult GameRequestHandler::leaveGame(RequestInfo requestInfo)
{
    GeneralResponseErrors errors;
    LeaveGameResponse leaveGameResponse(&errors);
    std::shared_ptr<IRequestHandler> nextHandler = std::move(this->m_room->isAdmin(this->m_user) ?
        this->m_handlerFactory.createRoomAdminRequestHandler(this->m_user, this->m_room) :
        this->m_handlerFactory.createRoomMemberRequestHandler(this->m_user, this->m_room));

    this->m_game->removePlayer(this->m_user);
    if(this->m_game->getPlayers().size() == 0)
        this->m_room->closeGame();

    RequestResult requestResult(
        JsonResponsePacketSerializer::serializeResponse(leaveGameResponse),
        nextHandler);
    return requestResult;
}