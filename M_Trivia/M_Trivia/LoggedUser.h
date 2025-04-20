#pragma once
#include <string>

struct LoggedUser {
	std::string m_username;
	std::string getUsername() {
		return this->m_username;
	}
};