#include "Game.hpp"

Game::Game(const std::vector<Question>& questions, const std::vector<LoggedUser>& neededPlayers, unsigned int gameId,
    unsigned int questionTimeLimit, Room* room)
    : m_gameId(gameId), m_questions(std::move(questions)), m_questionTimeLimit(questionTimeLimit),
    m_totalNeededPlayers(neededPlayers.size()), m_room(room), m_activePlayers(0), m_status(GameStatus::AnsweringQuestion), m_currQuestionIdx(0)
{
}

void Game::join(const LoggedUser& player) {
    this->m_activePlayers++;
    std::lock_guard<std::mutex> lock(m_playersMutex);
    Question shuffledCopy = Question(this->m_questions[0]);
    shuffledCopy.shuffle();
    m_players.emplace(player, PlayerGameData(shuffledCopy, std::chrono::steady_clock::now()));
    
    if (m_activePlayers == m_totalNeededPlayers) {
        this->m_room->enterGame();
    }
}

GameStatus Game::getStatus() const
{
    return this->m_status;
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

void Game::userAnswered(const LoggedUser& user)
{
    this->m_players[user].answeredLastQuestion = true;
}

void Game::moveToScoreBoard()
{
    this->m_status = GameStatus::ScoreBoardShow;
}


void Game::MoveToGameResults() {
    this->m_status = GameStatus::GameResultsShow;
}

double Game::getAnswerDouration(const std::chrono::time_point<std::chrono::steady_clock>& answerMoment) const
{
    return std::chrono::duration<double>(answerMoment - this->m_lastQuestionStartTime).count();
}


bool Game::didEveryoneAnswered() const
{
    for (const auto& [player, playerData] : this->m_players) {
        if (!playerData.answeredLastQuestion) {
            return false;
        }
    }
    return true;
}


void Game::setNextQuestion()
{
    this->m_status = GameStatus::AnsweringQuestion;

    this->m_currQuestionIdx++;
    std::lock_guard<std::mutex> lock(m_playersMutex);
    for (auto& [player, playerData] : this->m_players) {
        Question nextQuestionShuffledCopy(this->m_questions[this->m_currQuestionIdx]);
        nextQuestionShuffledCopy.shuffle();
        playerData.question = nextQuestionShuffledCopy;
        playerData.answeredLastQuestion = false;
    }
    this->m_lastQuestionStartTime = std::chrono::steady_clock::now();
}

bool Game::wasLastQuestion() const {
    return this->m_currQuestionIdx == this->m_questions.size() - 1;
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

unsigned int Game::getScoreShowingTime() const
{
    return m_room->getRoomPreview().roomData.scoreShowingTime;
}
