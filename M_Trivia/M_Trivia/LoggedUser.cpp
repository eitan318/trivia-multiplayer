#include "LoggedUser.hpp"

LoggedUser::LoggedUser(const std::string& username) : m_username(username)
{

}

std::string LoggedUser::getUsername() const {
	return m_username;
}
	


