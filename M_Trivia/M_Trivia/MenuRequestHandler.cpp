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

    LogoutResponse signOutResponse;
    LoginManager& manager = this->m_handlerFactory.getLoginManager();
    manager.logout(this->m_user.getUsername());

    RequestResult requestResult;
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(signOutResponse);
    requestResult.newHandler = new LoginRequestHandler(this->m_handlerFactory);
    return requestResult;
}

RequestResult MenuRequestHandler::getRooms(const RequestInfo& requestInfo) const
{
    //CreateRoomRequest request =
     //   JsonRequestPacketDeserializer<CreateRoomRequest>::deserializeRequest(requestInfo.buffer);

    GetRoomsResponse getRoomsResponse;
    RoomManager& roomManager = m_handlerFactory.getRoomManger();
    std::vector<RoomData> rooms = roomManager.getRooms();
    getRoomsResponse.rooms = rooms;
    getRoomsResponse.status = 0;//leshanot

    RequestResult requestResult;
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(getRoomsResponse);
    requestResult.newHandler = new MenuRequestHandler(this->m_user,this->m_handlerFactory);
    return requestResult;
}

RequestResult MenuRequestHandler::getPlayersInRoom(const RequestInfo& requestInfo) const
{
    GetPlayersInRoomRequest request = 
        JsonRequestPacketDeserializer<GetPlayersInRoomRequest>::deserializeRequest(requestInfo.buffer);

    GetPlayersInRoomResponse getPlayersInRoomResponse;
    int id = request.roomId;
    RoomManager& roomManager = m_handlerFactory.getRoomManger();

    Room room = roomManager.getRoom(id);
    std::vector<std::string> players = room.getAllUsers();
    getPlayersInRoomResponse.players = players;

    RequestResult requestResult;
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(getPlayersInRoomResponse);
    requestResult.newHandler = new MenuRequestHandler(this->m_user, this->m_handlerFactory);
    return requestResult;
}

RequestResult MenuRequestHandler::getPersonalStats(const RequestInfo& requestInfo) const
{
    //signoutRequest request = JsonRequestPacketDeserializer<GetPlayersInRoomRequest>::deserializeRequest(requestInfo.buffer);
    StatisticsManager& statsManager = this->m_handlerFactory.getStatisticsManger();
    GetPersonalStatisticsResponse personalStatsResponse(statsManager.getPlayerStatistics(this->m_user.getUsername()));


    RequestResult requestResult;
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(personalStatsResponse);
    requestResult.newHandler = new MenuRequestHandler(this->m_user,this->m_handlerFactory);
    return requestResult;
}

RequestResult MenuRequestHandler::getHighScore(const RequestInfo& requestInfo) const
{
    GetHighScoreRequest request = 
        JsonRequestPacketDeserializer<GetHighScoreRequest>::deserializeRequest(requestInfo.buffer);

    GetHighScoreResponse highScoreResponse;
    StatisticsManager& statsManager = this->m_handlerFactory.getStatisticsManger();
    highScoreResponse.statistics = statsManager.getBestScores(request.topPlayersLimit);

    RequestResult requestResult;
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(highScoreResponse);
    requestResult.newHandler = new MenuRequestHandler(this->m_user,this->m_handlerFactory);
    return requestResult;
}

RequestResult MenuRequestHandler::joinRoom(const RequestInfo& requestInfo) const
{
    JoinRoomRequest request = 
        JsonRequestPacketDeserializer<JoinRoomRequest>::deserializeRequest(requestInfo.buffer);

    JoinRoomResponse joinRoomResponse;
    int id = request.roomId;
    RoomManager& roomManager = m_handlerFactory.getRoomManger();
    try {
        Room& room = roomManager.getRoom(id);
        room.addUser(m_user);
        joinRoomResponse.status = (int)JoinRoomResponseStatus::Success;
    }
    catch (MyException err) {
        joinRoomResponse.status = (int)JoinRoomResponseStatus::UnknownRoomId;
    }
    RequestResult requestResult;
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(joinRoomResponse);
    requestResult.newHandler = new MenuRequestHandler(this->m_user,this->m_handlerFactory);
    return requestResult;
}

RequestResult MenuRequestHandler::createRoom(const RequestInfo& requestInfo) const
{
    CreateRoomRequest request =
        JsonRequestPacketDeserializer<CreateRoomRequest>::deserializeRequest(requestInfo.buffer);
    CreateRoomResponse createRoomResponse;
    RoomManager& roomManager = m_handlerFactory.getRoomManger();
 
    if ( request.questionCount > roomManager.getTotalQuestionsCount()) {
        createRoomResponse.status = (int)CreateRoomResponseStatus::TooMuchQuestions;
    }
    else {
        RoomData data;
        data.maxPlayers = request.maxUsers;
        data.numOfQuestionsInGame = request.questionCount;
        data.name = request.roomName;
        data.timePerQuestion = request.answerTimeout;
        createRoomResponse.roomId = roomManager.createRoom(this->m_user, data);
        createRoomResponse.status = (int)CreateRoomResponseStatus::Success;
    }

    RequestResult requestResult;
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(createRoomResponse);
    requestResult.newHandler = new MenuRequestHandler(this->m_user,this->m_handlerFactory);
    return requestResult;
}
