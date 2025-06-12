#pragma once
#include "HighScoreInfo.hpp"
#include "Question.hpp"
#include "UserRecord.hpp"
#include <list>
#include <string>
#include <vector>
#include "PlayerResults.hpp"

/**
 * @brief Interface for a database handling user and game-related data.
 */
class IDatabase {
public:
    /**
     * @brief Opens a connection to the database.
     * @return True if the database connection is successfully opened, false
     * otherwise.
     */
    virtual bool open() = 0;

    /**
     * @brief Closes the connection to the database.
     * @return True if the database connection is successfully closed, false
     * otherwise.
     */
    virtual bool close() = 0;

    /**
     * @brief Checks if a user exists in the database.
     * @param username The username to check.
     * @return 1 if the user exists, 0 otherwise.
     */
    virtual int doesUserExist(const std::string& username) const = 0;

    /**
     * @brief Verifies if the provided password matches the user's stored
     * password.
     * @param username The username to check.
     * @param password The password to verify.
     * @return 1 if the password matches, 0 otherwise.
     */
    virtual int doesPasswordMatch(const std::string& username,
        const std::string& password) const = 0;

    /**
     * @brief Adds a new user to the database.
     * @param userRecord The user information to add.
     * @return 1 if the user is successfully added, 0 otherwise.
     */
    virtual int addNewUser(const UserRecord& userRecord) const = 0;

    /**
     * @brief Creates the initial database structure, if it doesn't already exist.
     * @return True if the database is successfully initialized, false otherwise.
     */
    virtual bool createInitialDB() const = 0;

    /**
     * @brief Retrieves a specified number of random questions from the database.
     * @param amount The number of questions to retrieve.
     * @return A list of questions.
     */
    virtual std::vector<Question> getQuestions(int amount) const = 0;

    /**
     * @brief Retrieves the total number of answers submitted by a user.
     * @param username The username to query.
     * @return The total number of answers submitted.
     */
    virtual int getNumOfTotalAnswers(const std::string& username) const = 0;

    /**
     * @brief Retrieves the total number of correct answers submitted by a user.
     * @param username The username to query.
     * @return The total number of correct answers.
     */
    virtual int
        getNumOfTotalCorrectAnswers(const std::string& username) const = 0;

    /**
     * @brief Retrieves the total number of games played by a user.
     * @param username The username to query.
     * @return The total number of games played.
     */
    virtual int getNumOfPlayerGames(const std::string& username) const = 0;

    /**
     * @brief Retrieves the average answer time for a user.
     * @param username The username to query.
     * @return The average answer time in seconds.
     */
    virtual float getAvgAnswerTime(const std::string& username) const = 0;

    /**
     * @brief Checks if an email exists in the database.
     * @param email The email to check.
     * @return True if the email exists, false otherwise.
     */
    virtual bool emailExists(const std::string& email) const = 0;

    /**
     * @brief Retrieves user information based on their email.
     * @param email The email to query.
     * @return A UserRecord containing the user's information.
     */
    virtual UserRecord getUserRecord(const std::string& email) const = 0;

    /**
     * @brief Retrieves a list of high scores, ordered by score.
     * @param limit The maximum number of high scores to retrieve.
     * @return A vector of HighScoreInfo objects.
     */
    virtual std::vector<HighScoreInfo> getBestScores(int limit) const = 0;

    /**
     * @brief Updates a user's password.
     * @param username The username of the user.
     * @param newPassword The new password to set.
     */
    virtual void updatePassword(const std::string& username,
        const std::string& newPassword) const = 0;

    /**
     * @brief Retrieves the total number of questions in the database.
     * @return The total number of questions.
     */
    virtual unsigned int getQuestionsCount() const = 0;



    /**
	 * Adds a user's answer to the database.
	 *
	 * @param username The username of the player.
	 * @param gameId The ID of the game the answer belongs to.
	 * @param questionId The ID of the question being answered.
	 * @param isCorrect True if the answer is correct, otherwise false.
	 * @param score The score awarded for the answer.
	 * @param answerTimeSec The time taken by the user to answer, in seconds.
	 */
    virtual void addUserAnswer(const std::string& username, unsigned int gameId, unsigned int questionId,
        bool isCorrect, int score, double answerTimeSec) const = 0;

    /**
     * Creates a new game entry in the database.
     *
     * @return The ID of the newly created game.
     */
    virtual unsigned int createGame() const = 0;

    /**
     * Retrieves the results of a player for a specific game.
     *
     * @param username The username of the player.
     * @param gameId The ID of the game to retrieve results for.
     * @return An optional containing the player's results if found, or std::nullopt if no results are available.
     */
    virtual std::optional<PlayerResults> getPlayerResults(const std::string& username, unsigned int gameId) const = 0;


    virtual bool addExampleUsers() const = 0;
    
    /**
     * @brief Virtual destructor for proper cleanup of derived classes.
     */
    virtual ~IDatabase() = default;
};
