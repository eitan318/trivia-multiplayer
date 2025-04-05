#include "Server.h"

Server::Server()
	: m_database(new SqliteDatabase()),
	m_handlerFactory(*m_database),
	m_communicator(m_handlerFactory)
{}

Server::~Server()
{
	delete this->m_database;
}

void Server::run()
{
	//this->m_database = new SqliteDatabase();
	this->m_database->open();
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
