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
		throw MyException(std::string("Failed to prepare statement: ") + sqlite3_errmsg(db));
	}

	sqlite3_bind_text(stmt, 1, userRecord.username.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, userRecord.password.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 3, userRecord.email.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 4, userRecord.houseAddress.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 5, userRecord.phoneNumber.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 6, userRecord.birthDate.c_str(), -1, SQLITE_TRANSIENT);

	if (sqlite3_step(stmt) == SQLITE_DONE) {
		sqlite3_finalize(stmt);
	}
	else {
		sqlite3_finalize(stmt);
		throw std::runtime_error(std::string("Error: ") + userRecord.username);
	}
}

bool SqliteDatabase::createInitialDB()
{
	return createUsersTable() && createQuestionsTable() && addQuestions(50) && createAnswersTable() && createGamesTable();
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




bool SqliteDatabase::createGamesTable()
{
	const char* query = R"(
        CREATE TABLE Games (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL
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


bool SqliteDatabase::createAnswersTable()
{
	const char* query = R"(
    CREATE TABLE answers (
        username TEXT NOT NULL,
        question_id INTEGER NOT NULL,
        game_id INTEGER NOT NULL,
        correct INTEGER NOT NULL, -- 1 for true, 0 for false
        score INTEGER NOT NULL,
        answer_time REAL NOT NULL, -- Floating-point value for answer time
        PRIMARY KEY (username, game_id, question_id), -- Composite primary key
        FOREIGN KEY (question_id) REFERENCES Questions(id),
        FOREIGN KEY (username) REFERENCES Users(username),
        FOREIGN KEY (game_id) REFERENCES Games(id)
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




int SqliteDatabase::getNumOfTotalAnswers(const std::string& username)
{
	const char* query = "SELECT COUNT(*) FROM answers WHERE username = ?";
	sqlite3_stmt* stmt;

	if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
		throw std::runtime_error("Failed to prepare SQL statement.");
	}

	sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);

	int numOfTotalAnswers = 0;
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		numOfTotalAnswers = sqlite3_column_int(stmt, 0);
	}

	sqlite3_finalize(stmt);
	return numOfTotalAnswers;
}


int SqliteDatabase::getNumOfTotalCorrectAnswers(const std::string& username)
{
	const char* query = "SELECT COUNT(*) FROM answers WHERE username = ? AND correct = 1";
	sqlite3_stmt* stmt;

	if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
		throw std::runtime_error("Failed to prepare SQL statement.");
	}

	sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);

	int numOfCorrectAnswers = 0;
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		numOfCorrectAnswers = sqlite3_column_int(stmt, 0);
	}

	sqlite3_finalize(stmt);
	return numOfCorrectAnswers;
}


int SqliteDatabase::getNumOfPlayerGames(const std::string& username)
{
	const char* query = "SELECT COUNT(DISTINCT game_id) FROM answers WHERE username = ?";
	sqlite3_stmt* stmt;

	if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
		throw std::runtime_error("Failed to prepare SQL statement.");
	}

	sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);

	int games = 0;
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		games = sqlite3_column_int(stmt, 0);
	}

	sqlite3_finalize(stmt);
	return games;
}

float SqliteDatabase::getAvgAnswerTime(const std::string& username)
{
	const char* query = "SELECT AVG(answer_time) FROM answers WHERE username = ?";
	sqlite3_stmt* stmt;

	if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
		throw std::runtime_error("Failed to prepare SQL statement.");
	}

	sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);

	double avgAnswerTime = 0.0f; // Default value
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		if (sqlite3_column_type(stmt, 0) != SQLITE_NULL) {
			avgAnswerTime = sqlite3_column_double(stmt, 0);
		}
	}

	sqlite3_finalize(stmt);
	return avgAnswerTime;
}




std::list<HighScoreInfo> SqliteDatabase::getBestScores(int limit)
{
	const char* query = R"(
        SELECT a.username, a.game_id, g.name AS game_name, SUM(a.score) AS total_score
        FROM answers a
        JOIN Games g ON a.game_id = g.id
        GROUP BY a.game_id, a.username
        ORDER BY total_score DESC
        LIMIT ?;
    )";

	sqlite3_stmt* stmt;
	std::list<HighScoreInfo> results;

	// Prepare the SQL query
	if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
		throw std::runtime_error("Failed to prepare SQL statement.");
	}

	sqlite3_bind_int(stmt, 1, limit);

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		HighScoreInfo bsi;
		bsi.username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
		bsi.game_id = sqlite3_column_int(stmt, 1);
		bsi.game_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
		bsi.total_score = sqlite3_column_int(stmt, 3);

		results.push_back(bsi);
	}

	sqlite3_finalize(stmt);

	return results;
}

std::list<Question> SqliteDatabase::getQuestions(int amount)
{
	const char* query = R"(
    SELECT difficulty, category, question, answer, incorrect_answer_1,
    incorrect_answer_2, incorrect_answer_3 FROM questions LIMIT ?)";

	sqlite3_stmt* stmt;

	if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
		throw MyException(std::string("Failed to prepare statement: ") + sqlite3_errmsg(db));
	}

	sqlite3_bind_int(stmt, 1, amount);

	std::list<Question> questions;
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		// Create the Question object using data from the database
		Question q(
			std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0))),  // difficulty
			sqlite3_column_int(stmt, 1),  // category
			std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2))),  // question
			std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3))),  // correct_answer
			std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4))),  // incorrect_answer_1
			std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5))),  // incorrect_answer_2
			std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)))   // incorrect_answer_3
		);

		questions.push_back(q);
	}

	sqlite3_finalize(stmt);

	return questions;
}




