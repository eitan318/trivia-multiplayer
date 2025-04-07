#pragma once
#include "IDataBase.h"
#include "LoggedUser.h"
#include <vector>
#include "UserRecord.hpp"


class LoginManager {
private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
	LoginManager(IDatabase& database);
	~LoginManager() = default;
	LoginManager (const LoginManager&) = delete;
	LoginManager& operator=(const LoginManager&) = delete;
public:
	static LoginManager& getInstance(IDatabase& database);
	int signup(const UserRecord&);
	int login(const std::string username, const std::string password);
	void logout(const std::string username);
};