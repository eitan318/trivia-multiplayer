#pragma once
#include <string>
#include <list>
#include "UserRecord.hpp"
#include "Question.hpp"
class IDatabase {
public:
	virtual bool open() = 0;
	virtual bool close() = 0;
	virtual int doesUserExist(const std::string&) = 0;
	virtual int doesPasswordMatch(const std::string&, const std::string&) = 0;
	virtual int addNewUser(const UserRecord& userRecord) = 0;
	virtual bool createInitialDB() = 0;
	virtual std::list<Question> getQuestions(int amount) = 0;

};
