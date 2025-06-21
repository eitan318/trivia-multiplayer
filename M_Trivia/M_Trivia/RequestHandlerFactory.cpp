#include "RequestHandlerFactory.hpp"


#include "LoginRequestHandler.hpp"
#include "MenuRequestHandler.hpp"
#include "RoomAdminRequestHandler.hpp"
#include "GameRequestHandler.hpp"



RequestHandlerFactory::RequestHandlerFactory(IDatabase& database)
	: m_database(database),
	m_loginManager(LoginManager::getInstance(database)),
	m_statisticsManager(StatisticsManager::getInstance(database)),
	m_roomManager(RoomManager::getInstance(database)),
	m_gameManager(GameManager::getInstance(database))
{}



RequestHandlerFactory& RequestHandlerFactory::getInstance(IDatabase& database)
{
	static RequestHandlerFactory instance(database);
	return instance;
}

std::shared_ptr<IRequestHandler> RequestHandlerFactory::createLoginRequestHandler() const 
{
	return std::make_shared<LoginRequestHandler>(const_cast<RequestHandlerFactory&>(*this));
}

std::shared_ptr<IRequestHandler> RequestHandlerFactory::createMenuRequestHandler(const LoggedUser& loggedUser) const
{
	return std::make_shared<MenuRequestHandler>(loggedUser, const_cast<RequestHandlerFactory&>(*this));
}

std::shared_ptr<IRequestHandler> RequestHandlerFactory::createRoomAdminRequestHandler(const LoggedUser& loggedUser, unsigned int roomId) const
{
	return std::make_shared<RoomAdminRequestHandler>(const_cast<RequestHandlerFactory&>(*this), loggedUser, roomId);
}

std::shared_ptr<IRequestHandler> RequestHandlerFactory::createRoomRequestHandler(const LoggedUser& loggedUser, unsigned int roomId) const
{
	return std::make_shared<RoomRequestHandler>(const_cast<RequestHandlerFactory&>(*this), loggedUser, roomId);
}

std::shared_ptr<IRequestHandler> RequestHandlerFactory::createGameRequestHandler(LoggedUser user, std::shared_ptr<Game> game, RoomPreview& roomPreview)
{
	return std::make_shared<GameRequestHandler>(user,const_cast<RequestHandlerFactory&>(*this), game, roomPreview);
}

LoginManager& RequestHandlerFactory::getLoginManager() const
{
	return this->m_loginManager;
}

RoomManager& RequestHandlerFactory::getRoomManger() const
{
	return this->m_roomManager;
}

GameManager& RequestHandlerFactory::getGameManager() const
{
	return this->m_gameManager;
}

StatisticsManager& RequestHandlerFactory::getStatisticsManger() const
{
	return this->m_statisticsManager;
}
