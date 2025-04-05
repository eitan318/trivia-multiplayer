#pragma once
#include <iostream>

struct LoggedUser {
private:
	std::string m_username;

public:
	std::string getUsername() {
		return this->m_username;
	}
};