#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
#include <io.h>
#include <string>
#include <iostream>
#include "MyException.h"
#include "ApiClient.h"
#include "json.hpp"
#include <vector>
#include <list>


class SqliteDatabase : public IDatabase
{
public:
	static SqliteDatabase* getInstance();
	static void deleteInstance();
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

	static SqliteDatabase* _instance;
	sqlite3* db;
};

