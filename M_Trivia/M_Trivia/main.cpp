#pragma comment(lib, "ws2_32.lib")

#include "Server.hpp"
#include "WSAInitializer.hpp"

int main()
{
    WSAInitializer wsaInit;
    Server &server = Server::getInstance();
    server.run();
    return 0;
}
