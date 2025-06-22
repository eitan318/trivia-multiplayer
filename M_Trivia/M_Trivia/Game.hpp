#pragma once
#include "LoggedUser.hpp"
#include "Question.hpp"
#include "PlayerGameData.hpp"
#include "GameStatus.hpp"
#include "Room.hpp"
#include <map>
#include <vector>
#include <mutex>
#include <optional>
#include <chrono>

/**
 * @brief Represents a game, managing players, questions, and game state.
 */
class Game {
public:
    Game(const std::vector<Question>& questions, std::shared_ptr<RoomPreview> roomPreview, int gameId);



    // Deleted constructors and operators to prevent unintended copying or moving
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(Game&&) = delete;

    ~Game();

    // Player management
    /**
     * @brief Retrieves the player data for all players in the game.
     * @return Map of players to their game data.
     */
    std::map<LoggedUser, PlayerGameData> getPlayers();

    /**
     * @brief Checks if a user exists in the game.
     * @param user LoggedUser to check.
     * @return True if the user exists, false otherwise.
     */
    bool userExistsInGame(const LoggedUser& user) const;


    /**
     * @brief Adds a player to the game.
     * @param player The player to add.
     */
    void join(const LoggedUser& player);

    /**
     * @brief Removes one active player from the game.
     */
    void playerDeactivate(const LoggedUser& user);

    /**
     * @brief Gets the current number of active players.
     * @return Number of active players.
     */
    int countActivePlayers();

    /**
     * @brief Marks a user as having answered the current question.
     * @param user The player who answered.
     */
    void userAnswered(const LoggedUser& user);

    /**
     * @brief Checks if all active players have answered the current question.
     * @return True if all active players answered, false otherwise.
     */
    bool didEveryActiveAnswered() const;

    // Question management
    /**
     * @brief Gets the question assigned to a specific user.
     * @param user The player requesting a question.
     * @return The assigned question, or an empty optional if none is available.
     */
    std::optional<Question> getQuestionForUser(const LoggedUser& user);

    /**
     * @brief Advances the game to the next question.
     */
    void setNextQuestion();

    /**
     * @brief Checks if the current question is the last one.
     * @return True if it's the last question, false otherwise.
     */
    bool wasTheLastQuestion() const;

    /**
     * @brief Gets the current question index.
     * @return The index of the current question.
     */
    unsigned int getCurrQuestionIdx() const;

    // Game status and timing
    /**
     * @brief Gets the unique ID of the game.
     * @return Game ID.
     */
    unsigned int getId() const;

    /**
     * @brief Gets the time limit for answering each question.
     * @return Question time limit in seconds.
     */
    unsigned int getQuestionTimeLimit() const;

    /**
     * @brief Gets the time allocated for showing scores between rounds.
     * @return Score display time in seconds.
     */
    unsigned int getScoreShowingTime() const;

    /**
     * @brief Calculates the duration a user took to answer.
     * @param answerMoment The time the answer was submitted.
     * @return Duration in seconds as a double.
     */
    double getAnswerDouration(const std::chrono::time_point<std::chrono::steady_clock>& answerMoment) const;

    /**
     * @brief Gets the current status of the game.
     * @return The game status.
     */
    GameStatus getStatus() const;

    // Game state transitions
    /**
     * @brief Moves the game to the scoreboard phase.
     */
    void moveToScoreBoard();

    /**
     * @brief Moves the game to the results phase.
     */
    void moveToGameResults();



    unsigned int getQuestionsAmount();


    bool reachedTimeout() const;


private:
    // Immutable configuration
    const int m_gameId; 
    const int m_totalNeededPlayers;

    // Game data
    std::vector<Question> m_questions;
    std::map<LoggedUser, PlayerGameData> m_players; 
    int m_currQuestionIdx; 
    GameStatus m_status; 
    const RoomData m_roomData;

    // Timing
    std::chrono::time_point<std::chrono::steady_clock> m_lastQuestionStartTime; 

    // Thread safety
    mutable std::mutex m_playersMutex; 
    mutable std::mutex m_questionsMutex; 

    std::atomic<bool> m_stopTimeCheckThread{ false };
    std::thread m_timeCheckThread;
};
