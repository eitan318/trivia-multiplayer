#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
#include <io.h>
#include <iostream>

class SqliteDatabase : public IDatabase
{
public:
	SqliteDatabase();
	~SqliteDatabase();

	bool open();
	bool close();
	int doesUserExist(const std::string&);
	int doesPasswordMatch(const std::string&, const std::string&);
	int addNewUser(const std::string&, const std::string&, const std::string&);
private:
	bool createInitialDB();
	bool createUsersTable();
	sqlite3* db;
};

