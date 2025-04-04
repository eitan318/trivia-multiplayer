#include "Server.h"

Server::Server()
{

}

Server::~Server()
{
}

void Server::run()
{
	this->m_communicator.bindAndListen();
	std::thread t_connector = std::thread(&Communicator::startHandleRequest, &this->m_communicator);
	t_connector.detach();

	std::cout << "Write to server:" << std::endl;
	std::string input;
	do {
		std::cout << ">>> ";
		std::getline(std::cin, input);
	} while (input != "EXIT");

}
