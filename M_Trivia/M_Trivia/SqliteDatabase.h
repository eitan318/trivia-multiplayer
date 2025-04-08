#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
#include <io.h>
#include <iostream>
#include "MyException.h"
#include "ApiClient.h"
#include "json.hpp"


class SqliteDatabase : public IDatabase
{
public:
	static SqliteDatabase* getInstance();
	bool open();
	bool close();
	int doesUserExist(const std::string&);
	int doesPasswordMatch(const std::string&, const std::string&);
	int addNewUser(const UserRecord&);
private:
	~SqliteDatabase();
	SqliteDatabase() { };
	SqliteDatabase(const SqliteDatabase&) = delete;
	SqliteDatabase& operator=(const SqliteDatabase&) = delete;
	bool createInitialDB();
	bool createUsersTable();
	bool createQuestionsTable();
	bool createAnswersTable();
	bool createGamesTable();
	bool addQuestions(int amount);
	int getNumOfTotalAnswers(const std::string& username);
	int getNumOfTotalCorrectAnswers(const std::string& username);
	int getNumOfPlayerGames(const std::string& username);
	double getAvgAnswerTime(const std::string& username);
	std::list<HighScoreInfo> getBestScores(int limit);


	static SqliteDatabase* _instance;
	sqlite3* db;
};

