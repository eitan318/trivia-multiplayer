#pragma once
#include <string>
#include <list>
#include "UserRecord.hpp"
#include "Question.hpp"

struct HighScoreInfo {
	std::string username;
	std::string game_name;
	int total_score;
	int game_id;
};


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
	virtual std::list<HighScoreInfo> getBestScores(int limit) = 0;

};
