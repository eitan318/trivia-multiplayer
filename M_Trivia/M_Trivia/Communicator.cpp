#include "Communicator.h"
#include "Helper.h"


Communicator::Communicator(RequestHandlerFactory& handlerFactory) : m_handlerFactory(handlerFactory)
{
    // This server uses TCP. Hence, SOCK_STREAM & IPPROTO_TCP
    // If the server uses UDP, use SOCK_DGRAM & IPPROTO_UDP
    this->m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (this->m_serverSocket == INVALID_SOCKET) {
        int errorCode = WSAGetLastError();
        std::cerr << "socket() failed with error: " << errorCode << std::endl;
        throw std::runtime_error(std::string(__FUNCTION__) + " - socket() failed with error " + std::to_string(errorCode));
    }
}

Communicator::~Communicator()
{
    try {
        closesocket(this->m_serverSocket);
    }
    catch (const std::exception& e) {
        std::cerr << "Error in destructor: " << e.what() << std::endl;
    }
}

Communicator& Communicator::getInstance(RequestHandlerFactory& handlerFactory)
{
    static Communicator instance(handlerFactory);
    return instance;
}

void Communicator::startHandleRequest()
{
    while (true) {
        SOCKET client_socket = accept(this->m_serverSocket, NULL, NULL);
        if (client_socket == INVALID_SOCKET)
            throw std::exception(__FUNCTION__);

        std::cout << "Client accepted. Server and client can communicate." << std::endl;

        try {
            std::thread t_client(&Communicator::handleNewClient, this, client_socket);
            t_client.detach();
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
            closesocket(client_socket);
        }
    }
}

void Communicator::bindAndListen()
{
    const int port = 5554;

    struct sockaddr_in sa = { 0 };

    sa.sin_port = htons(port); // Port that server will listen on
    sa.sin_family = AF_INET;   // Must be AF_INET
    sa.sin_addr.s_addr = INADDR_ANY; // "INADDR_ANY" for any available IPs

    // Connects between the socket and the configuration (port, etc.)
    if (bind(this->m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR) {
        int errorCode = WSAGetLastError();
        std::cerr << "bind() failed with error: " << errorCode << std::endl;
        throw std::runtime_error(std::string(__FUNCTION__) + " - bind() failed with error " + std::to_string(errorCode));
    }

    // Start listening for incoming requests from clients
    if (listen(this->m_serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        int errorCode = WSAGetLastError();
        std::cerr << "bind() failed with error: " << errorCode << std::endl;
        throw std::runtime_error(std::string(__FUNCTION__) + " - listen() failed with error " + std::to_string(errorCode));
    }

    std::cout << "Listening on port " << port << std::endl;
}

void Communicator::handleNewClient(SOCKET sock)
{
    IRequestHandler* handler = new LoginRequestHandler(this->m_handlerFactory);
	this->m_clients.insert({ sock, handler});

    Helper::sendData(sock, "Hello");

    std::string msg = Helper::getStringPartFromSocket(sock, 5);
    std::cout << "Recieved: " << msg << std::endl;

    while (true) {
        RequestInfo requestInfo;
        int msgLen;
        std::string msgStr;

        try {
            requestInfo.code = Helper::getIntFromSocket(sock, 1);
            msgLen = Helper::getIntFromSocket(sock, sizeof(int));
            msgStr = Helper::getStringPartFromSocket(sock, msgLen);
        }
        catch (std::exception e) {
            std::cout << "Client probably left";
            break;
        }

        std::cout << "Recieved: " << msgStr << std::endl;
        requestInfo.buffer = std::vector<char>(msgStr.begin(), msgStr.end());
        RequestResult requestResult;
        requestResult = handler->handleRequest(requestInfo);
        if (handler != requestResult.newHandler)
            delete handler;
        handler = requestResult.newHandler;
        this->m_clients.at(sock) = handler;
        Helper::sendData(sock, requestResult.response);
    }
    delete handler;


}
