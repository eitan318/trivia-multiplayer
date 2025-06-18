#pragma once
#include "LoggedUser.hpp"
#include <map>
#include "Question.hpp"
#include "PlayerGameData.hpp"
#include <vector>
#include <mutex>
#include <optional>
#include "GameStatus.hpp"
#include "Room.hpp"


class Game {
public:
    Game(const std::vector<Question>& questions, const std::vector<LoggedUser>& neededPlayers, unsigned int gameId,
        unsigned int questionTimeLimit, Room* room);
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(Game&&) = delete;


    std::map<LoggedUser, PlayerGameData> getPlayers();
    std::optional<Question> getQuestionForUser(const LoggedUser& user);
    void setNextQuestion();
    unsigned int getQuestionTimeLimit() const;
    bool userExistsInGame(const LoggedUser& user) const;
    void removePlayer(const LoggedUser& user);
    unsigned int getId() const;
    void join(const LoggedUser& player);
    GameStatus getStatus() const;

    void moveToScoreBoard();
    void MoveToGameResults();
    double getAnswerDouration(const std::chrono::time_point<std::chrono::steady_clock>& answerMoment) const;

    void removeActivePlayer();
    int getActivePlayers();
    bool wasLastQuestion() const;


    unsigned int getCurrQuestionIdx() const;


    unsigned int getScoreShowingTime() const;

    void userAnswered(const LoggedUser& user);

    bool didEveryoneAnswered() const;

private:
    const unsigned int m_questionTimeLimit;
    std::vector<Question> m_questions;
    std::map<LoggedUser, PlayerGameData> m_players;
    const int m_gameId;
    int m_activePlayers;
    const int m_totalNeededPlayers;
    Room* m_room;
    int m_currQuestionIdx;
    GameStatus m_status;
    std::chrono::time_point<std::chrono::steady_clock> m_lastQuestionStartTime;

    mutable std::mutex m_playersMutex; // Protects m_players
    mutable std::mutex m_questionsMutex; // Protects m_questions

};
