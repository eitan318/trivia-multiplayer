#include "RequestHandlerFactory.h"


RequestHandlerFactory::RequestHandlerFactory(IDatabase& database)
	: m_database(database),
	m_loginManager(LoginManager::getInstance(database)),
	m_statisticsManager(StatisticsManager::getInstance(database)),
	m_roomManager(RoomManager::getInstance(database))
{}



RequestHandlerFactory& RequestHandlerFactory::getInstance(IDatabase& database)
{
	static RequestHandlerFactory instance(database);
	return instance;
}

std::unique_ptr<LoginRequestHandler> RequestHandlerFactory::createLoginRequestHandler() const 
{
	return std::make_unique<LoginRequestHandler>(const_cast<RequestHandlerFactory&>(*this));
}

std::unique_ptr<MenuRequestHandler> RequestHandlerFactory::createMenuRequestHandler(const LoggedUser& loggedUser) const
{
	return std::make_unique<MenuRequestHandler>(loggedUser, const_cast<RequestHandlerFactory&>(*this));
}

LoginManager& RequestHandlerFactory::getLoginManager() const
{
	return this->m_loginManager;
}

RoomManager& RequestHandlerFactory::getRoomManger() const
{
	return this->m_roomManager;
}

StatisticsManager& RequestHandlerFactory::getStatisticsManger() const
{
	return this->m_statisticsManager;
}
