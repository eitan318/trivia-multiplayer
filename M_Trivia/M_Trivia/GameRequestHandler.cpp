#include "GameRequestHandler.hpp"

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

}

RequestResult GameRequestHandler::handleRequest(const RequestInfo& requestInfo, SOCKET socket)
{

}

RequestResult GameRequestHandler::getQuestion(RequestInfo requestInfo)
{

}

RequestResult GameRequestHandler::submitAnswer(RequestInfo requestInfo)
{

}

RequestResult GameRequestHandler::getGamesResult(RequestInfo requestInfo)
{

}

RequestResult GameRequestHandler::leaveGame(RequestInfo requestInfo)
{

}