#pragma once
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "IDatabase.h"


class LoginRequestHandler;


class RequestHandlerFactory {
public:
	static RequestHandlerFactory& getInstance(IDatabase& database);
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();
private:
	IDatabase* m_database;
	LoginManager& m_loginManager;
	RequestHandlerFactory(IDatabase& database);
	RequestHandlerFactory(const RequestHandlerFactory&) = delete;
	RequestHandlerFactory& operator=(const RequestHandlerFactory&) = delete;
};