#include "Game.hpp"

Game::Game(std::vector<Question> questions, std::vector<LoggedUser> players, unsigned int roomId, unsigned int questionTimeLimit)
    : m_gameId(roomId), m_questions(questions), m_questionTimeLimit(questionTimeLimit)
{
    for (auto it = players.begin(); it != players.end(); it++)
    {
        this->m_players[it->getUsername()] = PlayerGameData{ 0, 0};
    }
}

std::map<LoggedUser, PlayerGameData> Game::getPlayers()
{
    return this->m_players;
}

std::optional<Question> Game::getQuestionForUser(const LoggedUser& user)
{
    if (m_players.find(user) == m_players.end()) {
        return std::nullopt;
    }
    else if (m_players[user].questionIdx >= this->m_questions.size()) {
        return std::nullopt;
    }
    Question currentQuestion = this->m_questions[m_players[user].questionIdx];
    return currentQuestion;    

}

bool Game::userExistsInGame(const LoggedUser& user) const
{
    return m_players.find(user) != m_players.end();
}

void Game::setNextQuestionForUser(const LoggedUser& user)
{
    this->m_players[user].questionIdx++;
    this->m_players[user].lastStartTime = std::time(nullptr);;
}

unsigned int Game::getQuestionTimeLimit() const
{
    return this->m_questionTimeLimit;
}

void Game::removePlayer(const LoggedUser& user)
{
    this->m_players.erase(user);
}

unsigned int Game::getId() const
{
    return this->m_gameId;
}

