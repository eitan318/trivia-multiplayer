#include "SqliteDatabase.h"
	
SqliteDatabase::SqliteDatabase()
{
}

SqliteDatabase::~SqliteDatabase()
{
	close(); 
}

bool SqliteDatabase::open()
{
	std::string dbFileName = "trivia_db.sqlite";

	int file_exist = _access(dbFileName.c_str(), 0);
	int res = sqlite3_open(dbFileName.c_str(), &db);
	if (file_exist != 0) {
		if (!createInitialDB()) {
			throw std::runtime_error("Failed to create tables");
			this->close();
			return false;
		}
	}
	return res == SQLITE_OK;
}

bool SqliteDatabase::close()
{
	if (db) {
		sqlite3_close(db);
		db = nullptr;
	}
	return true;
}


int SqliteDatabase::doesUserExist(const std::string& username)
{
	const char* query = "SELECT * FROM users WHERE username = ?";
	sqlite3_stmt* stmt;

	if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
		return false;
	}

	sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
	return sqlite3_step(stmt) == SQLITE_ROW;
}

int SqliteDatabase::doesPasswordMatch(const std::string& username, const std::string& password)
{
	const char* query = "SELECT password FROM users WHERE username = ?";
	sqlite3_stmt* stmt;

	if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
		return false;
	}

	sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		std::string realPassword = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
		sqlite3_finalize(stmt);
		return password == realPassword;
	}
	else {
		sqlite3_finalize(stmt);
		throw std::runtime_error(std::string("No user found with the username: ") + username);
	}
}

int SqliteDatabase::addNewUser(const std::string& username, const std::string& password, const std::string& email, const std::string& houseAddres,
	const std::string& phoneNumber, const std::string& birthDate)
{
	const char* query = "INSERT INTO users (username, password, email, house_addres, phone_number, birth_date) VALUES (?,?,?,?,?,?)";
	sqlite3_stmt* stmt;

	if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
		return false;
	}

	sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 3, email.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 4, houseAddres.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 5, phoneNumber.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 6, birthDate.c_str(), -1, SQLITE_TRANSIENT);

	if (sqlite3_step(stmt) == SQLITE_DONE) {
		sqlite3_finalize(stmt);
		return true;
	}
	else {
		sqlite3_finalize(stmt);
		throw std::runtime_error(std::string("Error: ") + username);
	}
}

bool SqliteDatabase::createInitialDB()
{
	return createUsersTable();
}

bool SqliteDatabase::createUsersTable() {
	const char* query = R"(
        CREATE TABLE Users (
            username TEXT PRIMARY KEY,
            password TEXT NOT NULL,
            email TEXT,
			house_addres TEXT,
			phone_number TEXT,
			birth_date TEXT
        )
    )";
	sqlite3_stmt* stmt;
	if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
		return false;
	}

	bool success = sqlite3_step(stmt) == SQLITE_DONE;
	sqlite3_finalize(stmt);
	return success;
}

