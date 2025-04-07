#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
#include <io.h>
#include <iostream>

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
	bool createInitialDB();
	bool createUsersTable();
	static SqliteDatabase* _instance;
	sqlite3* db;
};

