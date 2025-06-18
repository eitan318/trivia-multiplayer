#include "MenuRequestHandler.hpp"
#include "CreateRoomRequest.hpp"
#include "CreateRoomResponse.hpp"
#include "GetHighScoreRequest.hpp"
#include "GetHighScoreResponse.hpp"
#include "GetPersonalStatisticsResponse.hpp"
#include "GetPlayersInRoomRequest.hpp"
#include "GetPlayersInRoomResponse.hpp"
#include "GetRoomsResponse.hpp"
#include "JoinRoomRequest.hpp"
#include "JsonRequestPacketDeserializer.hpp"
#include "JsonResponsePacketSerializer.hpp"
#include "LoginManager.hpp"
#include "RequestHandlerFactory.hpp"
#include "RequestsCodes.hpp"
#include "RoomManager.hpp"
#include "RoomPreview.hpp"
#include "ServerErrorResponse.hpp"

MenuRequestHandler::MenuRequestHandler(const LoggedUser& user,
    RequestHandlerFactory& handlerFactory)
    : m_user(user), m_handlerFactory(handlerFactory) {}

// Checks if the request is relevant for menureqhandler
bool MenuRequestHandler::isRequestRelevant(
    const RequestInfo& requestInfo) const {
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

RequestResult
MenuRequestHandler::handleRequest(const RequestInfo& requestInfo) {
    switch (static_cast<RequestCodes>(requestInfo.code)) {
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
        RequestResult requestResult(
            JsonResponsePacketSerializer::serializeResponse(errorResponse),
            nullptr);
    }
}

void MenuRequestHandler::Cleanup()
{
    this->m_handlerFactory.getLoginManager().logout(this->m_user);
}

RequestResult MenuRequestHandler::logout(const RequestInfo& info) const {
    LogoutResponse logOutResponse(0);
    LoginManager& manager = this->m_handlerFactory.getLoginManager();
    manager.logout(this->m_user.getUsername());

    RequestResult requestResult(
        JsonResponsePacketSerializer::serializeResponse(logOutResponse),
        this->m_handlerFactory.createLoginRequestHandler());
    return requestResult;
}

RequestResult
MenuRequestHandler::getRooms(const RequestInfo& requestInfo) const {
    RoomManager& roomManager = m_handlerFactory.getRoomManger();
    std::vector<RoomPreview> rooms = roomManager.getRooms();
    GetRoomsResponse getRoomsResponse((unsigned int)GENERAL_SUCCESS_RESPONSE_STATUS, rooms);

    RequestResult requestResult(
        JsonResponsePacketSerializer::serializeResponse(getRoomsResponse),
        std::move(this->m_handlerFactory.createMenuRequestHandler(this->m_user)));
    return requestResult;
}

RequestResult
MenuRequestHandler::getPlayersInRoom(const RequestInfo& requestInfo) const {
    GetPlayersInRoomRequest request = JsonRequestPacketDeserializer<
        GetPlayersInRoomRequest>::deserializeRequest(requestInfo.buffer);

    int id = request.getRoomId();
    RoomManager& roomManager = m_handlerFactory.getRoomManger();

    Room* room = roomManager.getRoom(id);
    
    GetPlayersInRoomResponse getPlayersInRoomResponse((unsigned int)GENERAL_SUCCESS_RESPONSE_STATUS, room->getUsersVector());

    RequestResult requestResult(
        JsonResponsePacketSerializer::serializeResponse(getPlayersInRoomResponse),
        std::move(this->m_handlerFactory.createMenuRequestHandler(this->m_user)));
    return requestResult;
}

RequestResult
MenuRequestHandler::getPersonalStats(const RequestInfo& requestInfo) const {
    StatisticsManager& statsManager =
        this->m_handlerFactory.getStatisticsManger();
    PersonalStatistics ps =
        statsManager.getPlayerStatistics(this->m_user.getUsername());
    GetPersonalStatisticsResponse personalStatsResponse(ps, (unsigned int)GENERAL_SUCCESS_RESPONSE_STATUS);

    RequestResult requestResult(
        JsonResponsePacketSerializer::serializeResponse(personalStatsResponse),
        std::move(this->m_handlerFactory.createMenuRequestHandler(this->m_user)));
    return requestResult;
}

RequestResult
MenuRequestHandler::getHighScore(const RequestInfo& requestInfo) const {
    GetHighScoreRequest request =
        JsonRequestPacketDeserializer<GetHighScoreRequest>::deserializeRequest(
            requestInfo.buffer);

    StatisticsManager& statsManager =
        this->m_handlerFactory.getStatisticsManger();
    std::vector<HighScoreInfo> highestScores =
        statsManager.getBestScores(request.getTopPlayersLimit());

    GetHighScoreResponse highScoreResponse((unsigned int)GENERAL_SUCCESS_RESPONSE_STATUS, highestScores);

    RequestResult requestResult(
        JsonResponsePacketSerializer::serializeResponse(highScoreResponse),
        std::move(this->m_handlerFactory.createMenuRequestHandler(this->m_user)));
    return requestResult;
}

RequestResult
MenuRequestHandler::joinRoom(const RequestInfo& requestInfo) const {

    JoinRoomRequest request =
        JsonRequestPacketDeserializer<JoinRoomRequest>::deserializeRequest(
            requestInfo.buffer);

    int roomId = request.getRoomId();
    RoomManager& roomManager = m_handlerFactory.getRoomManger();

    GeneralResponseErrors joinRoomResponseErrors =
        m_handlerFactory.getRoomManger().joinRoom(roomId, this->m_user);

    JoinRoomResponse joinRoomResponse(std::make_unique<GeneralResponseErrors>(joinRoomResponseErrors));

    std::shared_ptr<IRequestHandler> nextHandler;

    if (joinRoomResponseErrors.statusCode() == 0)
        nextHandler = std::move(this->m_handlerFactory.createRoomRequestHandler(this->m_user, roomManager.getRoom(roomId)));
    else
        nextHandler = nullptr;

    RequestResult requestResult(
        JsonResponsePacketSerializer::serializeResponse(joinRoomResponse),
        nextHandler);

    return requestResult;
}

RequestResult
MenuRequestHandler::createRoom(const RequestInfo& requestInfo) const {
    CreateRoomRequest request =
        JsonRequestPacketDeserializer<CreateRoomRequest>::deserializeRequest(
            requestInfo.buffer);
   
    RoomData data = request.getRoomData();
    RoomManager& roomManager = m_handlerFactory.getRoomManger();

    CreateRoomResponseErrors createRoomResponseErrors =
        roomManager.createRoom(this->m_user, data);

    CreateRoomResponse createRoomResponse(std::make_unique<CreateRoomResponseErrors>(createRoomResponseErrors), data);


    std::shared_ptr<IRequestHandler> nextHandler;

    if (createRoomResponseErrors.statusCode() == 0)
        nextHandler = std::move(this->m_handlerFactory.createRoomAdminRequestHandler(this->m_user, roomManager.getRoom(data.id)));
    else
        nextHandler = nullptr;

    RequestResult requestResult(
        JsonResponsePacketSerializer::serializeResponse(createRoomResponse),
        nextHandler);
    return requestResult;
}
