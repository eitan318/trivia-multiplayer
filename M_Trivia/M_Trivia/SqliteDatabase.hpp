#pragma once
#include "HighScoreInfo.hpp"
#include "IDatabase.hpp"
#include "Question.hpp"
#include "UserRecord.hpp"
#include "PlayerResults.hpp"
#include "sqlite3.h"
#include <string>
#include <vector>

class SqliteDatabase : public IDatabase {
public:
    static SqliteDatabase& getInstance();
    bool open() override;
    bool close() override;
    int doesUserExist(const std::string&) const override;
    int doesPasswordMatch(const std::string&, const std::string&) const override;
    int addNewUser(const UserRecord&) const override;
    void addUserAnswer(const std::string& username, unsigned int gameId, unsigned int questionId,
        int chosenAnswerInQuestion, int score, double answerTimeSec) const override;
    std::optional<PlayerResults> getPlayerResults(const std::string& username, unsigned int gameId, unsigned int questionAmount) const;
    unsigned int createGame(const std::string& roomName, time_t startTime, bool is1v1) const override;
    bool emailExists(const std::string& email) const override;
    UserRecord getUserRecord(const std::string& email) const override;
    std::vector<HighScoreInfo> getBestScores(int limit, bool in1v1) const override;
    PersonalStatistics getPersonalStatistics(const std::string& username, bool is1v1Game) const override;
    std::vector<Question> getRandQuestions(int amount) const override;
    void updatePassword(const std::string& username,
        const std::string& newPassword) const override;
    unsigned int getQuestionsCount() const override;
    bool addExampleUsers() const override;

private:
    ~SqliteDatabase() { close(); };
    SqliteDatabase() {};
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
