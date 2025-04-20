#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(LoggedUser& user, RequestHandlerFactory& handlerFactory) : m_user(user),
m_handlerFactory(handlerFactory)
{
}

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& info) const
{
    return info.code == C_CreateRoomRequest &&
        info.code == C_GetPlayersInRoomRequest &&
        info.code == C_JoinRoomRequest;
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& info)
{
    switch (info.code) {
    case C_CreateRoomRequest:
    {
        return this->createRoom(info);
    }
    case C_GetPlayersInRoomRequest:
    {
        return this->getPlayersInRoom(info);
    }
    case C_JoinRoomRequest:
    {
        return this->joinRoom(info);
    }
    default:
        ErrorResponse errorResponse;
        errorResponse.message = "Invalid msg code.";

        RequestResult requestResult;
        requestResult.response = JsonResponsePacketSerializer::serializeResponse(errorResponse);
        requestResult.newHandler = new LoginRequestHandler(this->m_handlerFactory);

        return requestResult;
    }
    return {};
}

RequestResult MenuRequestHandler::signout(const RequestInfo& info)
{
    signoutRequest request = JsonRequestPacketDeserializer<GetPlayersInRoomRequest>::deserializeRequest(requestInfo.buffer);

    GetPlayersInRoomResponse gpirResponse;
    int id = request.roomId;
    RoomManager& roomManager = m_handlerFactory.getRoomManger();
    Room room = roomManager.getRoom(id);
    std::vector<std::string> players = room.getAllUsers();
    gpirResponse.players = players;

    RequestResult requestResult;
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(gpirResponse);
    requestResult.newHandler = new LoginRequestHandler(this->m_handlerFactory);
    return requestResult;
    return {};
}

RequestResult MenuRequestHandler::getRooms(const RequestInfo& requestInfo)
{
    getroomrequest request = JsonRequestPacketDeserializer<LoginRequest>::deserializeRequest(requestInfo.buffer);

    LoginResponse loginResponse;
    loginResponse.status = this->m_handlerFactory.getLoginManager().login(request.username, request.password);

    RequestResult requestResult;
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(loginResponse);
    requestResult.newHandler = new LoginRequestHandler(this->m_handlerFactory);
    return requestResult;
}


RequestResult MenuRequestHandler::getPlayersInRoom(const RequestInfo& requestInfo)
{
    GetPlayersInRoomRequest request = 
        JsonRequestPacketDeserializer<GetPlayersInRoomRequest>::deserializeRequest(requestInfo.buffer);

    GetPlayersInRoomResponse gpirResponse;
    int id = request.roomId;
    RoomManager& roomManager = m_handlerFactory.getRoomManger();

    Room room = roomManager.getRoom(id);
    std::vector<std::string> players = room.getAllUsers();
    gpirResponse.players = players;

    RequestResult requestResult;
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(gpirResponse);
    requestResult.newHandler = new LoginRequestHandler(this->m_handlerFactory);
    return requestResult;
}

RequestResult MenuRequestHandler::getPersonalStats(const RequestInfo& requestInfo)
{
    //GetPersonalStatisticsRequest
        return {};
}

RequestResult MenuRequestHandler::getHighScore(const RequestInfo& info)
{
    // TODO: Implement this function
    return {};
}

RequestResult MenuRequestHandler::joinRoom(const RequestInfo& requestInfo)
{
    JoinRoomRequest request = 
        JsonRequestPacketDeserializer<JoinRoomRequest>::deserializeRequest(requestInfo.buffer);

    NoDataResponse joinRoomResponse;
    int id = request.roomId;
    RoomManager& roomManager = m_handlerFactory.getRoomManger();
    try {
        Room room = roomManager.getRoom(id);
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

RequestResult MenuRequestHandler::createRoom(const RequestInfo& info)
{
    // TODO: Implement this function
    return {};
}
