#pragma once
#include "LoggedUser.hpp"
#include <map>
#include "Question.hpp"
#include "PlayerGameData.hpp"
#include <vector>
#include <mutex>
#include <optional>


class Game {
public:
    Game(std::vector<Question> questions, std::vector<LoggedUser> players, unsigned int roomId, unsigned int questionTimeLimit);
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    Game(Game&&) = delete;
    Game& operator=(Game&&) = delete;
    std::map<LoggedUser, PlayerGameData> getPlayers();
    std::optional<Question> getQuestionForUser(const LoggedUser& user);
    void setNextQuestionForUser(const LoggedUser& user);
    unsigned int getQuestionTimeLimit() const;
    bool userExistsInGame(const LoggedUser& user) const;

    void removePlayer(const LoggedUser& user);
    unsigned int getId() const;

private:
    const unsigned int m_questionTimeLimit;
    std::vector<Question> m_questions;
    std::map<LoggedUser, PlayerGameData> m_players;
    const int m_gameId;

    mutable std::mutex m_playersMutex; // Protects m_players
    mutable std::mutex m_questionsMutex; // Protects m_questions
};
