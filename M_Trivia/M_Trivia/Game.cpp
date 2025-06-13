#include "Game.hpp"

Game::Game(std::vector<Question> questions, std::vector<LoggedUser> players, unsigned int gameId, unsigned int questionTimeLimit)
    : m_gameId(gameId), m_questions(std::move(questions)), m_questionTimeLimit(questionTimeLimit)
{
    std::lock_guard<std::mutex> lock(m_playersMutex);
    for (const auto& player : players) {
        m_players[player] = PlayerGameData{ 0, std::time(nullptr) };
    }
}

std::map<LoggedUser, PlayerGameData> Game::getPlayers()
{
    std::lock_guard<std::mutex> lock(m_playersMutex);
    return m_players;
}

std::optional<Question> Game::getQuestionForUser(const LoggedUser& user)
{
    unsigned int questionIdx;
    {
        std::lock_guard<std::mutex> playersLock(m_playersMutex);
        if (m_players.find(user) == m_players.end()) {
            return std::nullopt;
        }

        questionIdx = m_players[user].questionIdx;
    }


    std::lock_guard<std::mutex> questionsLock(m_questionsMutex);
    if (questionIdx >= m_questions.size()) {
        return std::nullopt;
    }

    return m_questions[questionIdx];
}

bool Game::userExistsInGame(const LoggedUser& user) const
{
    std::lock_guard<std::mutex> lock(m_playersMutex);
    return m_players.find(user) != m_players.end();
}

void Game::setNextQuestionForUser(const LoggedUser& user)
{
    std::lock_guard<std::mutex> lock(m_playersMutex);
    auto it = m_players.find(user);
    if (it != m_players.end()) {
        it->second.questionIdx++;
        it->second.lastStartTime = std::time(nullptr);
    }
}

unsigned int Game::getQuestionTimeLimit() const
{
    return m_questionTimeLimit; 
}

void Game::removePlayer(const LoggedUser& user)
{
    std::lock_guard<std::mutex> lock(m_playersMutex);
    m_players.erase(user);
}

unsigned int Game::getId() const
{
    return m_gameId; // Immutable, no need for a lock.
}
