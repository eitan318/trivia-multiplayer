#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(const LoggedUser& user, RequestHandlerFactory& handlerFactory) : m_user(user),
m_handlerFactory(handlerFactory)
{
}

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
    switch (static_cast<RequestsCodes>(requestInfo.code)) {
    case RequestsCodes::CreateRoomRequest:
    case RequestsCodes::GetPlayersInRoomRequest:
    case RequestsCodes::JoinRoomRequest:
    case RequestsCodes::GetRoomsRequest:
        return true;
    default:
        return false;
    }
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& requestInfo) const
{
    switch (static_cast<RequestsCodes>(requestInfo.code)) {
    case RequestsCodes::CreateRoomRequest:
        return this->createRoom(requestInfo);
    case RequestsCodes::GetPlayersInRoomRequest:
        return this->getPlayersInRoom(requestInfo);
    case RequestsCodes::GetRoomsRequest:
        return this->getRooms(requestInfo);
    case RequestsCodes::JoinRoomRequest:
        return this->joinRoom(requestInfo);
    }
}

RequestResult MenuRequestHandler::signout(const RequestInfo& info) const
{
    //signoutRequest request = JsonRequestPacketDeserializer<GetPlayersInRoomRequest>::deserializeRequest(requestInfo.buffer);

    LogoutResponse signOutResponse(0);
    LoginManager& manager = this->m_handlerFactory.getLoginManager();
    manager.logout(this->m_user.getUsername());

    RequestResult requestResult;
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(signOutResponse);
    requestResult.newHandler = new LoginRequestHandler(this->m_handlerFactory);
    return requestResult;
}

RequestResult MenuRequestHandler::getRooms(const RequestInfo& requestInfo) const
{
    RoomManager& roomManager = m_handlerFactory.getRoomManger();
    std::vector<RoomData> rooms = roomManager.getRooms();
    GetRoomsResponse getRoomsResponse(0, rooms);

    RequestResult requestResult;
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(getRoomsResponse);
    requestResult.newHandler = new MenuRequestHandler(this->m_user,this->m_handlerFactory);
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
    requestResult.newHandler = new MenuRequestHandler(this->m_user, this->m_handlerFactory);
    return requestResult;
}

RequestResult MenuRequestHandler::getPersonalStats(const RequestInfo& requestInfo) const
{
    //signoutRequest request = JsonRequestPacketDeserializer<GetPlayersInRoomRequest>::deserializeRequest(requestInfo.buffer);
    StatisticsManager& statsManager = this->m_handlerFactory.getStatisticsManger();
    GetPersonalStatisticsResponse personalStatsResponse(0, statsManager.getPlayerStatistics(this->m_user.getUsername()));


    RequestResult requestResult;
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(personalStatsResponse);
    requestResult.newHandler = new MenuRequestHandler(this->m_user,this->m_handlerFactory);
    return requestResult;
}

RequestResult MenuRequestHandler::getHighScore(const RequestInfo& requestInfo) const
{
    GetHighScoreRequest request = 
        JsonRequestPacketDeserializer<GetHighScoreRequest>::deserializeRequest(requestInfo.buffer);


    StatisticsManager& statsManager = this->m_handlerFactory.getStatisticsManger();
    GetHighScoreResponse highScoreResponse(0, statsManager.getBestScores(request.getTopPlayersLimit()));
  
    RequestResult requestResult;
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(highScoreResponse);
    requestResult.newHandler = new MenuRequestHandler(this->m_user,this->m_handlerFactory);
    return requestResult;
}

RequestResult MenuRequestHandler::joinRoom(const RequestInfo& requestInfo) const
{
    JoinRoomRequest request = 
        JsonRequestPacketDeserializer<JoinRoomRequest>::deserializeRequest(requestInfo.buffer);


    int id = request.getRoomId();
    RoomManager& roomManager = m_handlerFactory.getRoomManger();
    unsigned int status;
    try {
        Room& room = roomManager.getRoom(id);
        room.addUser(m_user);
        status = (int)JoinRoomResponseStatus::Success;
    }
    catch (MyException err) {
        status = (int)JoinRoomResponseStatus::UnknownRoomId;
    }

    JoinRoomResponse joinRoomResponse(status);
    RequestResult requestResult;
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(joinRoomResponse);
    requestResult.newHandler = new MenuRequestHandler(this->m_user,this->m_handlerFactory);
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
    requestResult.newHandler = new MenuRequestHandler(this->m_user,this->m_handlerFactory);
    return requestResult;
}
