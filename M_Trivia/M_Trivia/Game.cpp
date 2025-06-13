#include "Game.hpp"

Game::Game(std::vector<Question> questions, std::vector<LoggedUser> players, unsigned int roomId, unsigned int questionTimeLimit)
    : m_gameId(roomId), m_questions(questions), m_questionTimeLimit(questionTimeLimit)
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
    std::lock_guard<std::mutex> lock(m_playersMutex);
    if (m_players.find(user) == m_players.end()) {
        return std::nullopt;
    }

    std::lock_guard<std::mutex> questionLock(m_questionsMutex);
    if (m_players[user].questionIdx >= m_questions.size()) {
        return std::nullopt;
    }

    return m_questions[m_players[user].questionIdx];
}

bool Game::userExistsInGame(const LoggedUser& user) const
{
    std::lock_guard<std::mutex> lock(m_playersMutex);
    return m_players.find(user) != m_players.end();
}

void Game::setNextQuestionForUser(const LoggedUser& user)
{
    std::lock_guard<std::mutex> lock(m_playersMutex);
    if (m_players.find(user) != m_players.end()) {
        m_players[user].questionIdx++;
        m_players[user].lastStartTime = std::time(nullptr);
    }
}

unsigned int Game::getQuestionTimeLimit() const
{
    return m_questionTimeLimit; // This does not need protection as it's immutable.
}

void Game::removePlayer(const LoggedUser& user)
{
    std::lock_guard<std::mutex> lock(m_playersMutex);
    m_players.erase(user);
}

unsigned int Game::getId() const
{
    return m_gameId; // This does not need protection as it's immutable.
}
