#include "LoginManager.h"

LoginManager::LoginManager(IDatabase& database)
{
	this->m_database = &database;
}
int LoginManager::signup(const std::string username, const std::string password, const std::string email) 
{
	if (this->m_database->doesUserExist(username)) 
	{
		return false;
	}
	return this->m_database->addNewUser(username, password, email);
}
int LoginManager::login(const std::string username, const std::string password)
{
	if (!this->m_database->doesUserExist(password)) 
	{
		return false;
	}
	if (this->m_database->doesPasswordMatch(username, password)) 
	{
		LoggedUser loggeduser;
		loggeduser.m_username = username;
		this->m_loggedUsers.push_back(loggeduser);
		return true;
	}
	return false;
	
}
void LoginManager::logout(const std::string username)
{
	for (auto loggedUser = this->m_loggedUsers.begin(); loggedUser != this->m_loggedUsers.end(); ++loggedUser) //goes through the vector
	{
		if (loggedUser->m_username == username) //if 
		{
			this->m_loggedUsers.erase(loggedUser);
			return; //stops after removing
		}
	}
}

