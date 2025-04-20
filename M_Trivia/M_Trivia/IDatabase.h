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
	virtual int doesUserExist(const std::string&) = 0;
	virtual int doesPasswordMatch(const std::string&, const std::string&) = 0;
	virtual int addNewUser(const UserRecord& userRecord) = 0;
	virtual bool createInitialDB() = 0;
	virtual std::list<Question> getQuestions(int amount) = 0;
	virtual int getNumOfTotalAnswers(const std::string& username) = 0;
	virtual int getNumOfTotalCorrectAnswers(const std::string& username) = 0;
	virtual int getNumOfPlayerGames(const std::string& username) = 0;
	virtual float getAvgAnswerTime(const std::string& username) = 0;
	virtual bool emailExists(const std::string& email) = 0;
	virtual UserRecord getUserRecord(const std::string& email) = 0;
	virtual std::vector<HighScoreInfo> getBestScores(int limit) = 0;
	virtual void updatePassword(const std::string& username, const std::string& newPassword) = 0;

};
