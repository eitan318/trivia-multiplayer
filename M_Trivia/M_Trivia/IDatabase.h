#pragma once
#include <string>
class IDatabase {
public:
	virtual bool open() = 0;
	virtual bool close() = 0;
	virtual int doesUserExist(const std::string&) = 0;
	virtual int doesPasswordMatch(const std::string&, const std::string&) = 0;
	virtual int addNewUser(const std::string&, const std::string&, const std::string&) = 0;
	virtual bool createInitialDB() = 0;

};
