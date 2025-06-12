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
    RequestHandlerFactory& handlerFactory,Room* room) : 
    m_gameManager(handlerFactory.getGameManager()),
    m_handlerFactory(handlerFactory),
    m_user(user),
    m_room(room)
{
    this->m_game = this->m_gameManager.createGame(room);
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
        errors.generalError = "User does not exist in game";
    }
    errors.statusCode = !errors.noErrors();
    GetQuestionResponse getQuestionResponse(&errors, quetionForUser.value());

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
    GeneralResponseErrors errors = this->m_gameManager.submitAnswer(this->m_user, this->m_game, answerId);

    std::optional<Question> questionUserChose = this->m_game->getQuestionForUser(m_user);

    SubmitAnswerResponse submitAnswerResponse(&errors, questionUserChose.value().getCorrectAnswerId());

    RequestResult requestResult(
        JsonResponsePacketSerializer::serializeResponse(submitAnswerResponse),
        nullptr);
    return requestResult;
}

RequestResult GameRequestHandler::getGameResults(RequestInfo requestInfo)
{
    std::vector<PlayerResults> playersResults = this->m_gameManager.getGameResults(this->m_game);
    PlayerResults d1("GUGUGAGA",12,21,12);
    PlayerResults d2("zaza", 12, 13, 14);
    PlayerResults d3("dawwfw",534,34,322);
    playersResults.emplace_back(d1);
    playersResults.emplace_back(d2);
    playersResults.emplace_back(d3);


    GetGameResultsResponse getGameResults(GENERAL_SUCCESS_RESPONSE_STATUS, playersResults);

    RequestResult requestResult(
        JsonResponsePacketSerializer::serializeResponse(getGameResults),
        nullptr);
    return requestResult;
}

RequestResult GameRequestHandler::leaveGame(RequestInfo requestInfo)
{
    this->m_room->removeUser(this->m_user);
    GeneralResponseErrors errors;
    LeaveGameResponse leaveGameResponse(&errors);

    RequestResult requestResult(
        JsonResponsePacketSerializer::serializeResponse(leaveGameResponse),
        std::move(this->m_handlerFactory.createMenuRequestHandler(this->m_user)));
    return requestResult;
}