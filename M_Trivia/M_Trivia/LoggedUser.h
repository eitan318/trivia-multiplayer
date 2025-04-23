#pragma once
#include <string>

struct LoggedUser {
	std::string m_username;
	std::string getUsername() const{
		return this->m_username;
	}
};