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
        bool isCorrect, int score, double answerTimeSec) const override;
    std::optional<PlayerResults> getPlayerResults(const std::string& username, unsigned int gameId) const override;
    unsigned int createGame() const override;
    int getNumOfTotalAnswers(const std::string& username) const override;
    int getNumOfTotalCorrectAnswers(const std::string& username) const override;
    int getNumOfPlayerGames(const std::string& username) const override;
    float getAvgAnswerTime(const std::string& username) const override;
    bool emailExists(const std::string& email) const override;
    UserRecord getUserRecord(const std::string& email) const override;
    std::vector<HighScoreInfo> getBestScores(int limit) const override;
    std::vector<Question> getQuestions(int amount) const override;
    void updatePassword(const std::string& username,
        const std::string& newPassword) const override;
    unsigned int getQuestionsCount() const override;
    virtual bool addExampleUsers() const override;


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
