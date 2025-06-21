#include "Game.hpp"

Game::Game(const std::vector<Question>& questions, std::shared_ptr<RoomPreview> roomPreview, int gameId)
    : m_gameId(gameId),
    m_questions(std::move(questions)),
    m_roomData(roomPreview->roomData),            
    m_totalNeededPlayers(roomPreview->currPlayersAmount),
    m_status(GameStatus::AnsweringQuestion),
    m_currQuestionIdx(0)
{
    this->m_lastQuestionStartTime = std::chrono::steady_clock::now();
}


void Game::join(const LoggedUser& player) {
    Question shuffledCopy = Question(this->m_questions[0]);
    shuffledCopy.shuffle();
    std::lock_guard<std::mutex> lock(m_playersMutex);
    m_players.emplace(player, PlayerGameData(shuffledCopy));
}

GameStatus Game::getStatus() const
{
    return this->m_status;
}

Game::~Game()
{
    // Signal the time-checking thread to stop
    m_stopTimeCheckThread.store(true);

    // Join the thread if it is joinable, ensuring it has finished executing
    if (m_timeCheckThread.joinable()) {
        m_timeCheckThread.join();
    }

    // Perform additional cleanup if necessary
    // For example, clear player data or other dynamically allocated resources
    {
        std::lock_guard<std::mutex> lock(m_playersMutex);
        m_players.clear();
    }

    {
        std::lock_guard<std::mutex> lock(m_questionsMutex);
        m_questions.clear();
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

void Game::userAnswered(const LoggedUser& user)
{
    this->m_players[user].answeredLastQuestion = true;
}

void Game::moveToScoreBoard()
{
    this->m_status = GameStatus::ScoreBoardShow;
}


void Game::moveToGameResults() {
    this->m_status = GameStatus::GameResultsShow;
}

unsigned int Game::getQuestionsAmount()
{
    return this->m_roomData.numOfQuestionsInGame;
}


double Game::getAnswerDouration(const std::chrono::time_point<std::chrono::steady_clock>& answerMoment) const
{
    return std::chrono::duration<double>(answerMoment - this->m_lastQuestionStartTime).count();
}


bool Game::didEveryActiveAnswered() const
{
    std::lock_guard<std::mutex> lock(m_playersMutex);
    for (const auto& [player, playerData] : this->m_players) {
        if (playerData.m_isActive && !playerData.answeredLastQuestion) {
            return false;
        }
    }
    return true;
}



bool Game::reachedTimeout() const
{
    auto now = std::chrono::steady_clock::now();
    double communicationDelay = 1;

    return std::chrono::duration<double>(now - this->m_lastQuestionStartTime).count() >
        this->m_roomData.timePerQuestion + communicationDelay;
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

bool Game::wasTheLastQuestion() const {
    return this->m_currQuestionIdx == this->m_questions.size() - 1;
}

unsigned int Game::getCurrQuestionIdx() const
{
    return this->m_currQuestionIdx;
}

unsigned int Game::getQuestionTimeLimit() const
{
    return this->m_roomData.timePerQuestion;
}


unsigned int Game::getId() const
{
    return m_gameId;
}

void Game::playerDeactivate(const LoggedUser& user)
{
    this->m_players[user].m_isActive = false;
}

int Game::countActivePlayers()
{
    std::lock_guard<std::mutex> lock(m_playersMutex);
    unsigned int countActive = 0;
    for (const auto& [player, playerData] : this->m_players) {
        if (playerData.m_isActive) {
            countActive++;
        }
    }
    return countActive;
}

unsigned int Game::getScoreShowingTime() const
{
    return m_roomData.scoreShowingTime;
}
