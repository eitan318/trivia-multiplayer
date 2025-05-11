#include "MenuRequestHandler.h"

#include "MyException.h"
#include "ServerErrorResponse.hpp"
#include "JsonResponsePacketSerializer.hpp"
#include "LogoutResponse.hpp"
#include "JsonRequestPacketDeserializer.hpp"
#include "RequestsCodes.hpp"
#include "JoinRoomRequest.hpp"
#include "CreateRoomRequest.hpp"
#include "GetPlayersInRoomRequest.hpp"
#include "GetHighScoreRequest.hpp"
#include "GetRoomsResponse.hpp"
#include "GetPlayersInRoomResponse.hpp"
#include "GetPersonalStatisticsResponse.hpp"
#include "GetHighScoreResponse.hpp"
#include "PersonalStatisticsRequest.hpp"
#include "CreateRoomResponse.hpp"
#include "RoomPreview.hpp"
#include "JoinRoomResponse.hpp"
#include "JoinRoomResponseErrors.hpp"
#include "LoginManager.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"

MenuRequestHandler::MenuRequestHandler(const LoggedUser& user, RequestHandlerFactory& handlerFactory) : m_user(user),
m_handlerFactory(handlerFactory)
{
}

//Checks if the request is relevant for menureqhandler
bool MenuRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
    switch (static_cast<RequestCodes>(requestInfo.code)) {
    case RequestCodes::CreateRoomRequest:
    case RequestCodes::GetPlayersInRoomRequest:
    case RequestCodes::JoinRoomRequest:
    case RequestCodes::GetRoomsRequest:
    case RequestCodes::LogoutRequest:
    case RequestCodes::GetHighScoresRequest:
    case RequestCodes::PersonalStatisticsRequest:    
        return true;
    default:
        return false;
    }
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& requestInfo) const
{
    switch (static_cast<RequestCodes>(requestInfo.code)) 
    {
    case RequestCodes::CreateRoomRequest:
        return this->createRoom(requestInfo);
    case RequestCodes::GetPlayersInRoomRequest:
        return this->getPlayersInRoom(requestInfo);
    case RequestCodes::GetRoomsRequest:
        return this->getRooms(requestInfo);
    case RequestCodes::JoinRoomRequest:
        return this->joinRoom(requestInfo);
    case RequestCodes::LogoutRequest:
        return this->logout(requestInfo);
    case RequestCodes::GetHighScoresRequest:
        return this->getHighScore(requestInfo);
    case RequestCodes::PersonalStatisticsRequest:
        return this->getPersonalStats(requestInfo);
    default:
		ServerErrorResponse errorResponse("Invalid msg code.");
		RequestResult requestResult;
		requestResult.response = JsonResponsePacketSerializer::serializeResponse(errorResponse);
		requestResult.newHandler = nullptr;
		return requestResult;
    }
    
}

RequestResult MenuRequestHandler::logout(const RequestInfo& info) const
{
    LogoutResponse logOutResponse(0);
    LoginManager& manager = this->m_handlerFactory.getLoginManager();
    manager.logout(this->m_user.getUsername());

    RequestResult requestResult;
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(logOutResponse);
    requestResult.newHandler = this->m_handlerFactory.createLoginRequestHandler();
    return requestResult;
}

RequestResult MenuRequestHandler::getRooms(const RequestInfo& requestInfo) const
{
    RoomManager& roomManager = m_handlerFactory.getRoomManger();
    std::vector<RoomPreview> rooms = roomManager.getRooms();
    GetRoomsResponse getRoomsResponse(0, rooms);

    RequestResult requestResult;
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(getRoomsResponse);
    requestResult.newHandler = std::move(this->m_handlerFactory.createMenuRequestHandler(this->m_user));
    return requestResult;
}

RequestResult MenuRequestHandler::getPlayersInRoom(const RequestInfo& requestInfo) const
{
    GetPlayersInRoomRequest request = 
        JsonRequestPacketDeserializer<GetPlayersInRoomRequest>::deserializeRequest(requestInfo.buffer);

    int id = request.getRoomId();
    RoomManager& roomManager = m_handlerFactory.getRoomManger();

    Room room = roomManager.getRoom(id);
    std::vector<LoggedUser> players = room.getAllUsers();
    GetPlayersInRoomResponse getPlayersInRoomResponse(0, players);

    RequestResult requestResult;
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(getPlayersInRoomResponse);
    requestResult.newHandler = std::move(this->m_handlerFactory.createMenuRequestHandler(this->m_user));
    return requestResult;
}

RequestResult MenuRequestHandler::getPersonalStats(const RequestInfo& requestInfo) const
{
    StatisticsManager& statsManager = this->m_handlerFactory.getStatisticsManger();
    PersonalStatistics ps = statsManager.getPlayerStatistics(this->m_user.getUsername());
    GetPersonalStatisticsResponse personalStatsResponse(ps, 0);

    RequestResult requestResult;
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(personalStatsResponse);
    requestResult.newHandler = std::move(this->m_handlerFactory.createMenuRequestHandler(this->m_user));
    return requestResult;
}

RequestResult MenuRequestHandler::getHighScore(const RequestInfo& requestInfo) const
{
    GetHighScoreRequest request = 
        JsonRequestPacketDeserializer<GetHighScoreRequest>::deserializeRequest(requestInfo.buffer);


    StatisticsManager& statsManager = this->m_handlerFactory.getStatisticsManger();
    std::vector<HighScoreInfo> highestScores = statsManager.getBestScores(request.getTopPlayersLimit());


    GetHighScoreResponse highScoreResponse(0, highestScores);
  
    RequestResult requestResult;
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(highScoreResponse);
    requestResult.newHandler = std::move(this->m_handlerFactory.createMenuRequestHandler(this->m_user));
    return requestResult;
}

RequestResult MenuRequestHandler::joinRoom(const RequestInfo& requestInfo) const
{
    JoinRoomRequest request = 
        JsonRequestPacketDeserializer<JoinRoomRequest>::deserializeRequest(requestInfo.buffer);


    int id = request.getRoomId();
    RoomManager& roomManager = m_handlerFactory.getRoomManger();
    JoinRoomResponseErrors errors;
    try {
        Room& room = roomManager.getRoom(id);
        if (room.getRoomPreview().roomData.maxPlayers == room.getAllUsers().size()) {
            errors.generalError = "Room is already full.";
        }
        else {
            room.addUser(m_user);
        }
    }
    catch (MyException err) {
        errors.generalError = "Room does not exist.";
    }
    
    errors.statusCode = !errors.noErrors();

    JoinRoomResponse joinRoomResponse(std::make_shared<JoinRoomResponseErrors>(errors));
    RequestResult requestResult;
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(joinRoomResponse);
    requestResult.newHandler = std::move(this->m_handlerFactory.createMenuRequestHandler(this->m_user));
    return requestResult;
}

RequestResult MenuRequestHandler::createRoom(const RequestInfo& requestInfo) const
{
    CreateRoomRequest request =
        JsonRequestPacketDeserializer<CreateRoomRequest>::deserializeRequest(requestInfo.buffer);

    RoomManager& roomManager = m_handlerFactory.getRoomManger();
    CreateRoomResponseErrors createRoonResponseErrors;
    unsigned int totalQuestionCount = roomManager.getTotalQuestionsCount();

    RoomData data;
    if ( request.getQuestionCount() > totalQuestionCount) {
        createRoonResponseErrors.questionCountError = "Too many questions, there are only: " + std::to_string(totalQuestionCount);
    }
    else {
        data.maxPlayers = request.getMaxUsers();
        data.numOfQuestionsInGame = request.getQuestionCount();
        data.name = request.getRoomName();
        data.timePerQuestion = request.getAnswerTimeout();
        roomManager.createRoom(this->m_user, data);
    }

    createRoonResponseErrors.statusCode = !createRoonResponseErrors.noErrors();

    CreateRoomResponse createRoomResponse(std::make_shared<CreateRoomResponseErrors>(createRoonResponseErrors), data);

    RequestResult requestResult;
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(createRoomResponse);
    requestResult.newHandler = std::move(this->m_handlerFactory.createMenuRequestHandler(this->m_user));
    return requestResult;
}
