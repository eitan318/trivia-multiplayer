#include "Game.hpp"

Game::Game(std::vector<Question> questions, std::vector<LoggedUser> players, unsigned int roomId, unsigned int questionTimeLimit)
    : m_gameId(roomId), m_questions(questions), m_questionTimeLimit(questionTimeLimit)
{
    for (auto it = players.begin(); it != players.end(); it++)
    {
        this->m_players[it->getUsername()] = questions[0];
    }
}

std::map<LoggedUser, Question> Game::getPlayers()
{
    return this->m_players;
}

std::optional<Question> Game::getQuestionForUser(const LoggedUser& user)
{
    if (m_players.find(user) == m_players.end()) {
        return std::nullopt;
    }
    Question currentQuestion = m_players[user];
    return currentQuestion;    

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

