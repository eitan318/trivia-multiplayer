#pragma once
#include <string>
#include <list>
#include <vector>
#include "UserRecord.hpp"
#include "Question.hpp"
#include "HighScoreinfo.hpp"


class IDatabase {
public:
	virtual bool open() = 0;
	virtual bool close() = 0;
	virtual int doesUserExist(const std::string&) const = 0;
	virtual int doesPasswordMatch(const std::string&, const std::string&) const = 0;
	virtual int addNewUser(const UserRecord& userRecord) const = 0;
	virtual bool createInitialDB() const = 0;
	virtual std::list<Question> getQuestions(int amount) const = 0;
	virtual int getNumOfTotalAnswers(const std::string& username) const = 0;
	virtual int getNumOfTotalCorrectAnswers(const std::string& username) const = 0;
	virtual int getNumOfPlayerGames(const std::string& username) const = 0;
	virtual float getAvgAnswerTime(const std::string& username) const = 0;
	virtual bool emailExists(const std::string& email) const = 0;
	virtual UserRecord getUserRecord(const std::string& email) const = 0;
	virtual std::vector<HighScoreInfo> getBestScores(int limit) const = 0;
	virtual void updatePassword(const std::string& username, const std::string& newPassword) const = 0;
	virtual unsigned int getQuestionsCount() const = 0;

};
