#pragma comment (lib, "ws2_32.lib")

#include "WSAInitializer.h"
#include "Server.h"

int main() {
	Server server = Server();
	server.run();
}