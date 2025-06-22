#pragma once
#include "IDatabase.hpp"
#include "vector"
#include "Game.hpp"
#include "Room.hpp"
#include "GeneralResponseErrors.hpp"
#include "PlayerResults.hpp"

/**
 * Manages the creation, deletion, and operations of games in the trivia application.
 */
class GameManager {
public:
    /**
     * Gets the singleton instance of the GameManager.
     *
     * @param database Reference to the database used for managing game data.
     * @return A reference to the singleton instance of the GameManager.
     */
    static GameManager& getInstance(IDatabase& database);

    void timeoutCheckLoop();

    /**
     * Creates a new game for the specified room.
     *
     * @param room Pointer to the room where the game is to be created.
     * @return A shared pointer to the newly created Game object.
     */
    std::shared_ptr<Game> createGame(std::shared_ptr<RoomPreview>);

    /**
     * Deletes a game with the specified game ID.
     *
     * @param gameId The ID of the game to delete.
     */
    void deleteGame(int gameId);

    std::shared_ptr<Game> getGame(unsigned int roomId);

    /**
     * Submits an answer for a user in a specified game.
     *
     * @param user The user submitting the answer.
     * @param game A shared pointer to the game in which the answer is submitted.
     * @param answerId The ID of the selected answer.
     * @return A GeneralResponseErrors value indicating the result of the submission (e.g., success or specific error).
     */
    GeneralResponseErrors submitAnswer(const LoggedUser& user, std::shared_ptr<Game> game,
        int answerId);

    /**
     * Retrieves the results for all players in a specified game.
     *
     * @param game A shared pointer to the game for which results are requested.
     * @return A vector of PlayerResults containing the results of each player in the game.
     */
    std::vector<PlayerResults> getGameResults(std::shared_ptr<Game> game) const;

    void handleTimeout(std::shared_ptr<Game> game);

    void leaveGame(std::shared_ptr<Game> game, std::shared_ptr<RoomPreview>, const LoggedUser& user);

    void actAfterQuestionAnsweringEnded(std::shared_ptr<Game> game);

    /**
     * Destructor for GameManager.
     */
    ~GameManager();

private:
    /**
     * Constructs a GameManager instance with a reference to the database.
     *
     * @param dataBase Reference to the database used for managing game data.
     */
    GameManager(IDatabase& dataBase);

    /**
     * Calculates the score for an answer based on difficulty level, answer time, correctness, and time limit.
     *
     * @param diffLevel The difficulty level of the question.
     * @param answerTime The time taken to answer, in seconds.
     * @param isCurrect True if the answer is correct, false otherwise.
     * @param timeLimit The time limit for answering the question.
     * @return The calculated score for the answer.
     */
    int calcAnswerScore(QuestionDifficultyLevelScores diffLevel, double answerTime, bool isCurrect, double timeLimit) const;

    std::map<unsigned int, std::shared_ptr<Game>> m_gamesByRoomId;
    IDatabase& m_database;
    mutable std::mutex m_gamesMutex; // Mutex to protect m_games

    std::atomic<bool> m_stopTimeoutThread;
    std::thread m_timeoutThread;
};
