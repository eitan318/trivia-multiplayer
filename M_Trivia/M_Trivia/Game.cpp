#include "Game.hpp"

Game::Game(std::vector<Question> questions, std::vector<LoggedUser> neededPlayers, unsigned int gameId,
    unsigned int questionTimeLimit, Room* room)
    : m_gameId(gameId), m_questions(std::move(questions)), m_questionTimeLimit(questionTimeLimit),
    m_totalNeededPlayers(neededPlayers.size()), m_room(room), m_activePlayers(0)
{
}

void Game::join(const LoggedUser& player) {
    this->m_activePlayers++;
    std::lock_guard<std::mutex> lock(m_playersMutex);
    Question shuffledCopy = Question(this->m_questions[0]);
    shuffledCopy.shuffle();
    m_players.emplace(player, PlayerGameData(0, shuffledCopy, std::time(nullptr)));
    
    if (m_activePlayers == m_totalNeededPlayers) {
        this->m_room->enterGame();
    }
}

std::map<LoggedUser, PlayerGameData> Game::getPlayers()
{
    std::lock_guard<std::mutex> lock(m_playersMutex);
    return m_players;
}

std::optional<Question> Game::getQuestionForUser(const LoggedUser& user)
{
    std::lock_guard<std::mutex> playersLock(m_playersMutex);
    if (m_players.find(user) == m_players.end()) {
        return std::nullopt;
    }
    return m_players.find(user)->second.question;
}

bool Game::userExistsInGame(const LoggedUser& user) const
{
    std::lock_guard<std::mutex> lock(m_playersMutex);
    return m_players.find(user) != m_players.end();
}

bool Game::setNextQuestionForUser(const LoggedUser& user)
{
    std::lock_guard<std::mutex> lock(m_playersMutex);
    auto it = m_players.find(user);
    if (it != m_players.end()) {
        if (it->second.questionIdx + 1 >= this->m_questions.size()) {
            return false;
        }
        it->second.questionIdx++;
        Question nextQuestionShuffledCopy(this->m_questions[it->second.questionIdx]);
        nextQuestionShuffledCopy.shuffle();
        it->second.question = nextQuestionShuffledCopy;
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
    return m_gameId; 
}

void Game::removeActivePlayer()
{
    m_activePlayers--;
}

int Game::getActivePlayers()
{
    return m_activePlayers;
}
