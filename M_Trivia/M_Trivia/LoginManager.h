#pragma once
#include "IDataBase.h"
#include "LoggedUser.h"
#include <vector>


class LoginManager {
private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
public:
	LoginManager(IDatabase& database);
	int signup(const std::string username, const std::string password, const std::string email);
	int login(const std::string username, const std::string password);
	void logout(const std::string username);
};