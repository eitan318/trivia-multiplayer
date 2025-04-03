#include "Server.h"

void Server::run()
{
	this->m_communicator.bindAndListen();
	std::thread t_connector = std::thread(&Communicator::startHandleRequest, &this->m_communicator);
	t_connector.detach();

	std::string input;
	do {
		std::cin >> input;

	} while (input != "EXIT");

}
