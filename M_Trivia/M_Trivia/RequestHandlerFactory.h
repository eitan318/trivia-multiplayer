#pragma once
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "IDatabase.h"
#include "RoomManager.h"


class LoginRequestHandler;


class RequestHandlerFactory {
public:
	static RequestHandlerFactory& getInstance(IDatabase& database);
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();
	RoomManager& getRoomManger();
private:
	RoomManager& m_roomManager;
	IDatabase* m_database;
	LoginManager& m_loginManager;
	RequestHandlerFactory(IDatabase& database);
	RequestHandlerFactory(const RequestHandlerFactory&) = delete;
	RequestHandlerFactory& operator=(const RequestHandlerFactory&) = delete;
};