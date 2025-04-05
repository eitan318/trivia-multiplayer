#include "LoginManager.h"

int LoginManager::signup(const std::string username, const std::string password, const std::string email) 
{
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
	return
}