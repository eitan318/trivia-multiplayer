#pragma once
#include <string>
#include "IDatabase.hpp"
#include "UserRecord.hpp"
#include "HighScoreInfo.hpp"
#include "Question.hpp"
#include <vector>
#include <list>
#include "sqlite3.h"





class SqliteDatabase : public IDatabase
{
public:
	static SqliteDatabase& getInstance();
	bool open();
	bool close();
	int doesUserExist(const std::string&) const;
	int doesPasswordMatch(const std::string&, const std::string&) const;
	int addNewUser(const UserRecord&) const;
	int getNumOfTotalAnswers(const std::string& username) const;
	int getNumOfTotalCorrectAnswers(const std::string& username) const;
	int getNumOfPlayerGames(const std::string& username) const;
	float getAvgAnswerTime(const std::string& username) const;
	bool emailExists(const std::string& email) const;
	UserRecord getUserRecord(const std::string& email) const;
	std::vector<HighScoreInfo> getBestScores(int limit) const;
	std::list<Question> getQuestions(int amount) const;
    void updatePassword(const std::string& username, const std::string& newPassword) const;
	unsigned int getQuestionsCount() const;
private:
	~SqliteDatabase() { close(); };
	SqliteDatabase() { };
	SqliteDatabase(const SqliteDatabase&) = delete;
	SqliteDatabase& operator=(const SqliteDatabase&) = delete;
	bool createInitialDB() const;
	bool createUsersTable() const;
	bool createQuestionsTable() const;
	bool createAnswersTable() const;
	bool createGamesTable() const;
	bool addQuestions(int amount) const;

	sqlite3* db;
};

