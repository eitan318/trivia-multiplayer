#include "SqliteDatabase.hpp"

#include "ApiClient.hpp"
#include "MyException.hpp"
#include "json.hpp"
#include <io.h>
#include <iostream>

SqliteDatabase& SqliteDatabase::getInstance() {
    static SqliteDatabase instance;
    return instance;
}

bool SqliteDatabase::open() {
    if (db) {
        // Database is already opened
        return true;
    }

    const std::string dbFileName = "trivia_db.sqlite";

    // Check if the database file exists
    int fileExists = _access(dbFileName.c_str(), 0);
    int result = sqlite3_open(dbFileName.c_str(), &db);

    if (result != SQLITE_OK) {
        // Opening the database failed
        db = nullptr;
        std::cerr << "Error: Failed to open database. Error code: " << result
            << "\n";
        return false;
    }

    // If the file didn't exist, create the database and initialize tables
    if (fileExists != 0) {
        if (!createInitialDB()) {
            std::cerr << "Error: Failed to initialize database tables.\n";
            this->close(); // Ensure resources are released
            return false;
        }
    }

    return true;
}

bool SqliteDatabase::close() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
    return true;
}

int SqliteDatabase::doesUserExist(const std::string& username) const {
    const char* query = "SELECT * FROM users WHERE username = ?";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db)
            << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
    return sqlite3_step(stmt) == SQLITE_ROW;
}

int SqliteDatabase::doesPasswordMatch(const std::string& username,
    const std::string& password) const {
    const char* query = "SELECT password FROM users WHERE username = ?";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db)
            << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string realPassword =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        sqlite3_finalize(stmt);
        return password == realPassword;
    }
    else {
        sqlite3_finalize(stmt);
        throw std::runtime_error(std::string("No user found with the username: ") +
            username);
    }
}

int SqliteDatabase::addNewUser(const UserRecord& userRecord) const {
    const char* query =
        "INSERT INTO users (username, password, email, house_address, "
        "phone_number, birth_date) VALUES (?,?,?,?,?,?)";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        throw MyException(std::string("Failed to prepare statement: ") +
            sqlite3_errmsg(db));
    }

    sqlite3_bind_text(stmt, 1, userRecord.username.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, userRecord.password.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, userRecord.email.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, userRecord.houseAddress.c_str(), -1,
        SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, userRecord.phoneNumber.c_str(), -1,
        SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 6, userRecord.birthDate.c_str(), -1,
        SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_DONE) {
        sqlite3_finalize(stmt);
    }
    else {
        sqlite3_finalize(stmt);
        throw std::runtime_error(std::string("Error: ") + userRecord.username);
    }
}

void SqliteDatabase::addUserAnswer(const std::string& username, unsigned int gameId,
    unsigned int questionId, int chosenAnswerInQuestion, int score, double answerTimeSec) const {

    const char* query = R"(
    INSERT INTO answers (username, question_id, game_id, chosen_answer, score, answer_time)
    VALUES (?, ?, ?, ?, ?, ?)
    )";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        throw MyException(std::string("Failed to prepare statement: ") +
            sqlite3_errmsg(db));
    }

    // Bind the parameters to the query
    if (sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_int(stmt, 2, questionId) != SQLITE_OK ||
        sqlite3_bind_int(stmt, 3, gameId) != SQLITE_OK ||
        sqlite3_bind_int(stmt, 4, chosenAnswerInQuestion) != SQLITE_OK ||
        sqlite3_bind_int(stmt, 5, score) != SQLITE_OK ||
        sqlite3_bind_double(stmt, 6, answerTimeSec) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        throw MyException(std::string("Failed to bind parameters: ") +
            sqlite3_errmsg(db));
    }

    // Execute the statement
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw MyException(std::string("Failed to execute statement: ") +
            sqlite3_errmsg(db));
    }

    // Finalize the statement
    sqlite3_finalize(stmt);
}



bool SqliteDatabase::createInitialDB() const {
    return createUsersTable() && createQuestionsTable() && addQuestions(50) &&
        createAnswersTable() && createGamesTable() && addExampleUsers();
}

bool SqliteDatabase::createUsersTable() const {
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
        throw MyException(std::string("Failed to prepare statement: ") +
            sqlite3_errmsg(db));
    }

    bool success = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return success;
}

bool SqliteDatabase::createQuestionsTable() const {
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
        throw MyException(std::string("Failed to prepare statement: ") +
            sqlite3_errmsg(db));
    }

    bool success = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return success;
}

bool SqliteDatabase::createGamesTable() const {
    const char* query = R"(
        CREATE TABLE Games (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            room_name TEXT NOT NULL,
            start_time INTEGER NOT NULL,
            is_1v1_game INTEGER NOT NULL
        )
    )";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        throw MyException(std::string("Failed to prepare statement: ") +
            sqlite3_errmsg(db));
    }

    bool success = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return success;
}

bool SqliteDatabase::createAnswersTable() const {
    const char* query = R"(
    CREATE TABLE answers (
        username TEXT NOT NULL,
        question_id INTEGER NOT NULL,
        game_id INTEGER NOT NULL,
        chosen_answer INTEGER NOT NULL, -- 0 for true ans, then 1,2,3
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
        throw MyException(std::string("Failed to prepare statement: ") +
            sqlite3_errmsg(db));
    }

    bool success = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return success;
}

bool SqliteDatabase::addQuestions(int amount) const {
    std::string url = ApiClient::generateTriviaQuestionsUrl(45, 9, "multiple");
    std::string questionsJsonStr = ApiClient::getQuestionsJson(url.c_str());
    nlohmann::json questionsJson = nlohmann::json::parse(questionsJsonStr);

    if (questionsJson["response_code"] != 0) {
        std::cerr << "Failed to fetch questions from API. Response code: "
            << questionsJson["response_code"] << std::endl;
        return false;
    }

    try {
        for (const auto& question : questionsJson["results"]) {
            std::string questionText = question["question"];
            std::string difficulty = question["difficulty"];
            std::string correctAnswer = question["correct_answer"];
            std::string category = question["category"];
            std::vector<std::string> wrongAnswers;

            for (const auto& wrong : question["incorrect_answers"]) {
                wrongAnswers.push_back(wrong.get<std::string>());
            }

            if (wrongAnswers.size() != 3) {
                throw MyException("Expected exactly 3 incorrect answers for question: " + questionText);
            }

            QuestionRecord qRec(questionText, difficulty, correctAnswer, wrongAnswers, category);

            if (!addQuestionToDB(qRec)) {
                throw MyException("Failed to add question to database.");
            }
        }
    }
    catch (const MyException& error) {
        std::cerr << "Exception: " << error.what() << std::endl;
        return false;
    }

    return true;
}


bool SqliteDatabase::addQuestionToDB(QuestionRecord& questionRecord) const {
    const std::string& difficulty = questionRecord.getDifficultyLevel();
    const std::string& category = questionRecord.getCategory();
    const std::string& questionText = questionRecord.getQuestion();
    const std::string& correctAnswer = questionRecord.getRightAnswer();
    const std::vector<std::string>& incorrectAnswers = questionRecord.getWrongAnswers();

    if (incorrectAnswers.size() != 3) {
        throw MyException("Expected exactly 3 incorrect answers for question: " + questionText);
    }

    const char* insertQuery = R"(
        INSERT INTO Questions (difficulty, category, question, answer, incorrect_answer_1, incorrect_answer_2, incorrect_answer_3)
        VALUES (?, ?, ?, ?, ?, ?, ?)
    )";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, insertQuery, -1, &stmt, nullptr) != SQLITE_OK) {
        throw MyException("Failed to prepare insert statement: " + std::string(sqlite3_errmsg(db)));
    }

    try {
        sqlite3_bind_text(stmt, 1, difficulty.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, category.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, questionText.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, correctAnswer.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, incorrectAnswers[0].c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 6, incorrectAnswers[1].c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 7, incorrectAnswers[2].c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            throw MyException("Failed to insert question: " + std::string(sqlite3_errmsg(db)));
        }
    }
    catch (...) {
        sqlite3_finalize(stmt);
        throw;
    }

    sqlite3_finalize(stmt);
    return true;
}


std::optional<PlayerResults> SqliteDatabase::getPlayerResults(const std::string& username, unsigned int gameId, unsigned int questionAmount) const {
    const char* query = R"(
    SELECT 
        username,
        SUM(CASE WHEN chosen_answer = 0 THEN 1 ELSE 0 END) AS correctAnswerCount,
        SUM(CASE WHEN chosen_answer != 0  AND chosen_answer != -1 THEN 1 ELSE 0 END) AS wrongAnswerCount,
        SUM(score),
        AVG(answer_time)
    FROM answers
    WHERE username = ? AND game_id = ?
    GROUP BY username
)";


    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        throw MyException(std::string("Failed to prepare statement: ") + sqlite3_errmsg(db));
    }

    // Bind parameters
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, gameId);

    // Execute the query and process the result
    std::optional<PlayerResults> result;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        result = PlayerResults(
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)), // username
            sqlite3_column_int(stmt, 1),                                // correctAnswerCount
            sqlite3_column_int(stmt, 2),                                // wrongAnswerCount
            sqlite3_column_int(stmt, 3),                                // score
            sqlite3_column_double(stmt, 4),                         // averageAnswerTime
            questionAmount
        );
    }

    sqlite3_finalize(stmt);
    return result;
}



unsigned int SqliteDatabase::createGame(const std::string& roomName, time_t startTime, bool is1v1) const {

    const char* query = R"(
        INSERT INTO Games (room_name, start_time, is_1v1_game) VALUES (?, ?, ?)
    )";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        throw MyException(std::string("Failed to prepare statement: ") +
            sqlite3_errmsg(db));
    }

    if (sqlite3_bind_text(stmt, 1, roomName.c_str(), -1, SQLITE_TRANSIENT) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        throw MyException(std::string("Failed to bind roomName parameter: ") +
            sqlite3_errmsg(db));
    }

    if (sqlite3_bind_int64(stmt, 2, static_cast<sqlite3_int64>(startTime)) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        throw MyException(std::string("Failed to bind startTime parameter: ") +
            sqlite3_errmsg(db));
    }

    if (sqlite3_bind_int64(stmt, 3, static_cast<sqlite3_int64>(is1v1)) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        throw MyException(std::string("Failed to bind is_1v1_game parameter: ") +
            sqlite3_errmsg(db));
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw MyException(std::string("Failed to execute statement: ") +
            sqlite3_errmsg(db));
    }

    unsigned int gameId = static_cast<unsigned int>(sqlite3_last_insert_rowid(db));

    sqlite3_finalize(stmt);

    return gameId;
}





UserRecord SqliteDatabase::getUserRecord(const std::string& email) const {
    const char* query =
        R"(SELECT username, password, email, phone_number, house_address, birth_date
                           FROM users WHERE email = ?)";
    sqlite3_stmt* stmt = nullptr;

    try {
        // Prepare the SQL statement
        if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error(
                std::string("Failed to prepare SQL statement: ") +
                sqlite3_errmsg(db));
        }

        // Bind email to the query
        if (sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_TRANSIENT) !=
            SQLITE_OK) {
            throw std::runtime_error(std::string("Failed to bind email: ") +
                sqlite3_errmsg(db));
        }

        // Execute the query and check for a row
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            UserRecord userRecord;
            userRecord.username =
                sqlite3_column_text(stmt, 0)
                ? reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0))
                : "";
            userRecord.password =
                sqlite3_column_text(stmt, 1)
                ? reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1))
                : "";
            userRecord.email =
                sqlite3_column_text(stmt, 2)
                ? reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2))
                : "";
            userRecord.phoneNumber =
                sqlite3_column_text(stmt, 3)
                ? reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3))
                : "";
            userRecord.houseAddress =
                sqlite3_column_text(stmt, 4)
                ? reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4))
                : "";
            userRecord.birthDate =
                sqlite3_column_text(stmt, 5)
                ? reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5))
                : "";

            sqlite3_finalize(stmt); // Finalize the statement before returning
            return userRecord;
        }
        else {
            // No row found
            throw MyException("No user record found for the provided email.");
        }
    }
    catch (...) {
        if (stmt) {
            sqlite3_finalize(stmt); // Ensure resources are cleaned up
        }
        throw; // Re-throw the exception for the caller to handle
    }
}


std::vector<HighScoreInfo> SqliteDatabase::getBestScores(int limit, bool in1v1) const {
    const char* query = R"(
        SELECT a.username, a.game_id, g.room_name, g.start_time, SUM(a.score) AS total_score
        FROM answers a
        JOIN Games g ON a.game_id = g.id AND g.is_1v1_game = ?
        GROUP BY a.game_id, a.username
        ORDER BY total_score DESC
        LIMIT ?;
    )";

    sqlite3_stmt* stmt;
    std::vector<HighScoreInfo> results;

    // Prepare the SQL query
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error(std::string("Failed to prepare SQL statement: ") + sqlite3_errmsg(db));
    }

    sqlite3_bind_int(stmt, 1, in1v1);
    sqlite3_bind_int(stmt, 2, limit);

    for (unsigned int i = 1; sqlite3_step(stmt) == SQLITE_ROW; i++) {
        HighScoreInfo bsi;
        bsi.username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        bsi.gameId = sqlite3_column_int(stmt, 1);
        bsi.roomName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        bsi.startTime = sqlite3_column_int64(stmt, 3);
        bsi.totalScore = sqlite3_column_int(stmt, 4);
        bsi.rank = i;

        results.push_back(bsi);
    }

    sqlite3_finalize(stmt);

    return results;
}

PersonalStatistics SqliteDatabase::getPersonalStatistics(const std::string& username, bool is1v1Game) const
{
    const char* query = R"(
        SELECT 
            COUNT(*) FILTER (WHERE chosen_answer = 0) AS correct_answer_count,
            COUNT(DISTINCT game_id) AS num_of_player_games,
            COUNT(*) FILTER (WHERE chosen_answer != -1) AS total_answer_count,
            AVG(answer_time) AS avg_answer_time 
        FROM answers a
        JOIN games g ON a.game_id = g.id
        WHERE a.username = ? AND g.is_1v1_game = ?
    )";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error(
            std::string("Failed to prepare SQL statement: ") + sqlite3_errmsg(db));
    }

    // Bind parameters
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, static_cast<int>(is1v1Game));

    PersonalStatistics personalStats;

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        personalStats = PersonalStatistics(
            username,
            sqlite3_column_int(stmt, 0),  // correct_answer_count
            sqlite3_column_int(stmt, 1),  // num_of_player_games
            sqlite3_column_int(stmt, 2),  // total_answer_count
            sqlite3_column_type(stmt, 3) != SQLITE_NULL
            ? sqlite3_column_double(stmt, 3)  // avg_answer_time
            : 0.0  
        );
    }

    sqlite3_finalize(stmt);
    return personalStats;
}

std::vector<Question> SqliteDatabase::getRandQuestions(int amount) const {
    const char* query = R"(
    SELECT id, difficulty, category, question, answer, incorrect_answer_1,
    incorrect_answer_2, incorrect_answer_3 FROM questions ORDER BY RANDOM() LIMIT ?)";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        throw MyException(std::string("Failed to prepare statement: ") +
            sqlite3_errmsg(db));
    }

    // Bind the number of questions to fetch
    sqlite3_bind_int(stmt, 1, amount);

    std::vector<Question> questions;

    // Iterate through the result set
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Question q(
            sqlite3_column_int(stmt, 0), // id
            std::string(reinterpret_cast<const char*>(
                sqlite3_column_text(stmt, 1))), // difficulty
            std::string(reinterpret_cast<const char*>(
                sqlite3_column_text(stmt, 2))), // category
            std::string(reinterpret_cast<const char*>(
                sqlite3_column_text(stmt, 3))), // question
            std::string(reinterpret_cast<const char*>(
                sqlite3_column_text(stmt, 4))), // correct_answer
            std::string(reinterpret_cast<const char*>(
                sqlite3_column_text(stmt, 5))), // incorrect_answer_1
            std::string(reinterpret_cast<const char*>(
                sqlite3_column_text(stmt, 6))), // incorrect_answer_2
            std::string(reinterpret_cast<const char*>(
                sqlite3_column_text(stmt, 7)))  // incorrect_answer_3
        );

        questions.emplace_back(q);
    }

    // Finalize the statement to free resources
    sqlite3_finalize(stmt);

    return questions;
}



unsigned int SqliteDatabase::getQuestionsCount() const {
    const char* query = R"(
    SELECT COUNT(*) FROM questions)";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        throw MyException(std::string("Failed to prepare statement: ") +
            sqlite3_errmsg(db));
    }

    std::unique_ptr<sqlite3_stmt, decltype(&sqlite3_finalize)> stmtGuard(
        stmt, sqlite3_finalize);

    if (sqlite3_step(stmt) != SQLITE_ROW) {
        throw MyException("Failed to execute query or no result returned.");
    }

    int count = sqlite3_column_int(stmt, 0);

    return static_cast<unsigned int>(count);
}

void SqliteDatabase::updatePassword(const std::string& username,
    const std::string& newPassword) const {
    const char* query = R"(UPDATE users SET password = ? WHERE username = ?)";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        throw MyException(std::string("Failed to prepare statement: ") +
            sqlite3_errmsg(db));
    }

    try {
        sqlite3_bind_text(stmt, 1, newPassword.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_TRANSIENT);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            throw MyException(std::string("Failed to execute update: ") +
                sqlite3_errmsg(db));
        }

        sqlite3_finalize(stmt);
    }
    catch (...) {
        sqlite3_finalize(stmt);
        throw; // Re-throw the exception to propagate error.
    }
}

bool SqliteDatabase::emailExists(const std::string& email) const {
    const char* query = "SELECT * FROM users WHERE email = ?";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        throw MyException(std::string("Failed to execute update: ") +
            sqlite3_errmsg(db));
    }

    sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_TRANSIENT);
    bool res = sqlite3_step(stmt) == SQLITE_ROW;
    sqlite3_finalize(stmt);
    return res;
}

bool SqliteDatabase::addExampleUsers() const {
    UserRecord d;
    d.username = '1';
    d.password = 'a';
    UserRecord d2;
    d2.username = '2';
    d2.password = 'a';
    UserRecord d1;
    d1.username = '3';
    d1.password = 'a';
    UserRecord d3;
    d3.username = '4';
    d3.password = 'a';
    UserRecord d4;
    d4.username = '5';
    d4.password = 'a';
    UserRecord d5;
    d5.username = '6';
    d5.password = 'a';
    addNewUser(d);
    addNewUser(d1);
    addNewUser(d2);
    addNewUser(d3);
    addNewUser(d4);
    addNewUser(d5);
    return true;
}