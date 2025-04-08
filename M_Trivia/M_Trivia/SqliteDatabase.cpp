#include "SqliteDatabase.h"

SqliteDatabase* SqliteDatabase::_instance = nullptr;
	

SqliteDatabase::~SqliteDatabase()
{
	close(); 
}

SqliteDatabase* SqliteDatabase::getInstance()
{
	if (_instance == nullptr) {
		_instance = new SqliteDatabase();
	}
	else {
		throw std::exception("Cannot instansiate a singleton twice. Eitan");
	}
	return _instance;
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

int SqliteDatabase::addNewUser(const UserRecord& userRecord)
{
	const char* query = "INSERT INTO users (username, password, email, house_address, phone_number, birth_date) VALUES (?,?,?,?,?,?)";
	sqlite3_stmt* stmt;

	if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
		return false;
	}

	sqlite3_bind_text(stmt, 1, userRecord.username.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, userRecord.password.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 3, userRecord.email.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 4, userRecord.houseAddress.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 5, userRecord.phoneNumber.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 6, userRecord.birthDate.c_str(), -1, SQLITE_TRANSIENT);

	if (sqlite3_step(stmt) == SQLITE_DONE) {
		sqlite3_finalize(stmt);
		return true;
	}
	else {
		sqlite3_finalize(stmt);
		throw std::runtime_error(std::string("Error: ") + userRecord.username);
	}
}

bool SqliteDatabase::createInitialDB()
{
	return createUsersTable() && createQuestionsTable() && addQuestions(50);
}

bool SqliteDatabase::createUsersTable() {
	const char* query = R"(
        CREATE TABLE Users (
            username TEXT PRIMARY KEY,
            password TEXT NOT NULL,
            email TEXT,
			house_address TEXT,
			phone_number TEXT,
			birth_date TEXT
        )
    )";
	sqlite3_stmt* stmt;
	if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
		throw MyException( std::string("Failed to prepare statement: ") + sqlite3_errmsg(db));
	}

	bool success = sqlite3_step(stmt) == SQLITE_DONE;
	sqlite3_finalize(stmt);
	return success;
}

bool SqliteDatabase::createQuestionsTable()
{
	const char* query = R"(
        CREATE TABLE Questions (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
			difficulty TEXT NOT NULL,
			category TEXT,
			question TEXT NOT NULL,
			answer TEXT NOT NULL,
            incorrect_answer_1 TEXT,
            incorrect_answer_2 TEXT,
            incorrect_answer_3 TEXT
        )
    )";
	sqlite3_stmt* stmt;
	if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
		throw MyException(std::string("Failed to prepare statement: ") + sqlite3_errmsg(db));
	}

	bool success = sqlite3_step(stmt) == SQLITE_DONE;
	sqlite3_finalize(stmt);
	return success;

}


bool SqliteDatabase::addQuestions(int amount)
{
	std::string url = ApiClient::generateTriviaQuestionsUrl(45, 9, "multiple");
	std::string questionsJsonStr = ApiClient::getQuestionsJson(url.c_str()); // Fetch questions JSON
	nlohmann::json questionsJson = nlohmann::json::parse(questionsJsonStr);

	// Check if the API response code is successful
	if (questionsJson["response_code"] != 0) {
		std::cerr << "Failed to fetch questions from API. Response code: "
			<< questionsJson["response_code"] << std::endl;
		return false;
	}

	// Prepare the SQL insert query
	const char* insertQuery = R"(
        INSERT INTO Questions (difficulty, category, question, answer, incorrect_answer_1, incorrect_answer_2, incorrect_answer_3)
        VALUES (?, ?, ?, ?, ?, ?, ?)
    )";

	sqlite3_stmt* stmt;
	if (sqlite3_prepare_v2(db, insertQuery, -1, &stmt, nullptr) != SQLITE_OK) {
		throw MyException(std::string("Failed to prepare insert statement: ") + sqlite3_errmsg(db));
	}

	// Parse and insert questions into the database
	try {
		for (const auto& question : questionsJson["results"]) {
			const std::string& difficulty = question["difficulty"];
			const std::string& category = question["category"];
			const std::string& questionText = question["question"];
			const std::string& correctAnswer = question["correct_answer"];
			const auto& incorrectAnswers = question["incorrect_answers"];

			// Ensure `incorrect_answers` has 3 entries
			if (incorrectAnswers.size() != 3) {
				throw MyException("Expected exactly 3 incorrect answers for question: " + questionText);
			}

			// Extract incorrect answers as separate strings
			const std::string incorrectAnswer1 = incorrectAnswers[0].get<std::string>();
			const std::string incorrectAnswer2 = incorrectAnswers[1].get<std::string>();
			const std::string incorrectAnswer3 = incorrectAnswers[2].get<std::string>();

			// Bind values to the SQL statement
			sqlite3_bind_text(stmt, 1, difficulty.c_str(), -1, SQLITE_STATIC);
			sqlite3_bind_text(stmt, 2, category.c_str(), -1, SQLITE_STATIC);
			sqlite3_bind_text(stmt, 3, questionText.c_str(), -1, SQLITE_STATIC);
			sqlite3_bind_text(stmt, 4, correctAnswer.c_str(), -1, SQLITE_STATIC);
			sqlite3_bind_text(stmt, 5, incorrectAnswer1.c_str(), -1, SQLITE_STATIC);
			sqlite3_bind_text(stmt, 6, incorrectAnswer2.c_str(), -1, SQLITE_STATIC);
			sqlite3_bind_text(stmt, 7, incorrectAnswer3.c_str(), -1, SQLITE_STATIC);

			// Execute the statement
			if (sqlite3_step(stmt) != SQLITE_DONE) {
				throw MyException(std::string("Failed to insert question: ") + sqlite3_errmsg(db));
			}

			sqlite3_reset(stmt);
		}
	}
	catch (...) {
		sqlite3_finalize(stmt);
		throw; // Rethrow the exception after cleaning up
	}

	sqlite3_finalize(stmt);
	return true;
}








