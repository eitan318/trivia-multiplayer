#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(const LoggedUser& user, RequestHandlerFactory& handlerFactory) : m_user(user),
m_handlerFactory(handlerFactory)
{
}

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
    switch (static_cast<RequestCodes>(requestInfo.code)) {
    case RequestCodes::CreateRoomRequest:
    case RequestCodes::GetPlayersInRoomRequest:
    case RequestCodes::JoinRoomRequest:
    case RequestCodes::GetRoomsRequest:
    case RequestCodes::LogoutRequest:
    case RequestCodes::GetHighScoresRequest:
        return true;
    default:
        return false;
    }
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& requestInfo) const
{
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
    requestResult.newHandler = std::make_unique<LoginRequestHandler>(this->m_handlerFactory);
    return requestResult;
}

RequestResult MenuRequestHandler::getRooms(const RequestInfo& requestInfo) const
{
    RoomManager& roomManager = m_handlerFactory.getRoomManger();
    std::vector<RoomData> rooms = roomManager.getRooms();
    GetRoomsResponse getRoomsResponse(0, rooms);

    RequestResult requestResult;
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(getRoomsResponse);
    requestResult.newHandler = std::make_unique<MenuRequestHandler>(this->m_user, this->m_handlerFactory);
    return requestResult;
}

RequestResult MenuRequestHandler::getPlayersInRoom(const RequestInfo& requestInfo) const
{
    GetPlayersInRoomRequest request = 
        JsonRequestPacketDeserializer<GetPlayersInRoomRequest>::deserializeRequest(requestInfo.buffer);

    int id = request.getRoomId();
    RoomManager& roomManager = m_handlerFactory.getRoomManger();

    Room room = roomManager.getRoom(id);
    std::vector<std::string> players = room.getAllUsers();
    GetPlayersInRoomResponse getPlayersInRoomResponse(0, players);

    RequestResult requestResult;
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(getPlayersInRoomResponse);
    requestResult.newHandler = std::make_unique<MenuRequestHandler>(this->m_user, this->m_handlerFactory);
    return requestResult;
}

RequestResult MenuRequestHandler::getPersonalStats(const RequestInfo& requestInfo) const
{
    StatisticsManager& statsManager = this->m_handlerFactory.getStatisticsManger();
    GetPersonalStatisticsResponse personalStatsResponse(0, statsManager.getPlayerStatistics(this->m_user.getUsername()));


    RequestResult requestResult;
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(personalStatsResponse);
    requestResult.newHandler = std::make_unique<MenuRequestHandler>(this->m_user, this->m_handlerFactory);
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
    requestResult.newHandler = std::make_unique<MenuRequestHandler>(this->m_user, this->m_handlerFactory);
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
        room.addUser(m_user);
    }
    catch (MyException err) {
        errors.generalError = "Room does not exist.";
    }
    
    errors.statusCode = !errors.noErrors();

    JoinRoomResponse joinRoomResponse(std::make_shared<JoinRoomResponseErrors>(errors));
    RequestResult requestResult;
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(joinRoomResponse);
    requestResult.newHandler = std::make_unique<MenuRequestHandler>(this->m_user, this->m_handlerFactory);
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
    requestResult.newHandler = std::make_unique<MenuRequestHandler>(this->m_user, this->m_handlerFactory);
    return requestResult;
}
