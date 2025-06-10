#include "GameRequestHandler.hpp"
#include "RequestsCodes.hpp"
#include "ServerErrorResponse.hpp"
#include "JsonResponsePacketSerializer.hpp"
#include "GetGameResultsResponse.hpp"
#include "SubmitAnswerResponse.hpp"
#include "LeaveGameResponse.hpp"
#include "GetQuestionResponse.hpp"

GameRequestHandler::GameRequestHandler(const LoggedUser& user,
    RequestHandlerFactory& handlerFactory,
    Game& game,
    GameManager& gameManager) : m_game(game),
    m_gameManager(gameManager),
    m_handlerFactory(handlerFactory),
    m_user(user)
{}

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
            return this->getGamesResult(requestInfo);
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
    Question quetionForUser = this->m_game.getQuestionForUser(m_user);
    GetQuestionResponse getQuestionResponse(GENERAL_SUCCESS_RESPONSE_STATUS, quetionForUser);

    RequestResult requestResult(
        JsonResponsePacketSerializer::serializeResponse(getQuestionResponse),
        std::move(this->m_handlerFactory.createMenuRequestHandler(this->m_user)));
    return requestResult;
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo requestInfo)
{
    
}

RequestResult GameRequestHandler::getGamesResult(RequestInfo requestInfo)
{
    std::map<LoggedUser,GameData> allUsers = this->m_game.getPlayers();
    std::vector<PlayerResults> playersResults;
    for (auto it = allUsers.begin(); it != allUsers.end(); ++it) {
        const LoggedUser& user = it->first;
        const GameData& data = it->second;
        PlayerResults currPlayer;
        currPlayer.averageAnswerTime = data.averageAnswerTime;
        currPlayer.correctAnswerCount = data.correctAnswerCount;
        currPlayer.wrongAnswerCount = data.wrongAnswerCount;
        currPlayer.username = user.getUsername();
        playersResults.emplace_back(currPlayer);
    }

    GetGameResultsResponse getGameResults(GENERAL_SUCCESS_RESPONSE_STATUS, playersResults);

    RequestResult requestResult(
        JsonResponsePacketSerializer::serializeResponse(getGameResults),
        std::move(this->m_handlerFactory.createMenuRequestHandler(this->m_user)));
    return requestResult;
}

RequestResult GameRequestHandler::leaveGame(RequestInfo requestInfo)
{
    this->m_game.removePlayer();
    GeneralResponseErrors* errors;
    LeaveGameResponse leaveGameResponse(errors);

    RequestResult requestResult(
        JsonResponsePacketSerializer::serializeResponse(leaveGameResponse),
        std::move(this->m_handlerFactory.createMenuRequestHandler(this->m_user)));
    return requestResult;
}