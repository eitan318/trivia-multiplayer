#pragma comment (lib, "ws2_32.lib")

#include "WSAInitializer.hpp"
#include "Server.hpp"

int main() {
	WSAInitializer wsaInit;
	Server& server = Server::getInstance();
	server.run();
	return 0;
}



