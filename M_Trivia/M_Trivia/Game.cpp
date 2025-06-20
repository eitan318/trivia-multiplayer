#include "Game.hpp"

Game::Game(const std::vector<Question>& questions, const std::vector<LoggedUser>& neededPlayers, unsigned int gameId,
    unsigned int questionTimeLimit, Room* room)
    : m_gameId(gameId), m_questions(std::move(questions)), m_questionTimeLimitSeconds(questionTimeLimit),
    m_totalNeededPlayers(neededPlayers.size()), m_room(room), m_activePlayers(0), m_status(GameStatus::AnsweringQuestion), m_currQuestionIdx(0)
{
    this->m_lastQuestionStartTime = std::chrono::steady_clock::now();

    // Start the time-checking thread
    m_timeCheckThread = std::thread(&Game::timeCheckLoop, this);
}

void Game::join(const LoggedUser& player) {
    this->m_activePlayers++;
    std::lock_guard<std::mutex> lock(m_playersMutex);
    Question shuffledCopy = Question(this->m_questions[0]);
    shuffledCopy.shuffle();
    m_players.emplace(player, PlayerGameData(shuffledCopy));

    if (m_activePlayers == m_totalNeededPlayers) {
        this->m_room->enterGame();
    }
}

GameStatus Game::getStatus() const
{
    return this->m_status;
}

Game::~Game()
{
    m_stopTimeCheckThread.store(true); // Signal the thread to stop
    if (m_timeCheckThread.joinable()) {
        m_timeCheckThread.join(); // Wait for the thread to finish
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


void Game::MoveToGameResults() {
    this->m_status = GameStatus::GameResultsShow;
}


double Game::getAnswerDouration(const std::chrono::time_point<std::chrono::steady_clock>& answerMoment) const
{
    return std::chrono::duration<double>(answerMoment - this->m_lastQuestionStartTime).count();
}


bool Game::didEveryActiveAnswered() const
{
    unsigned int countAnswered = 0;
    for (const auto& [player, playerData] : this->m_players) {
        if (playerData.answeredLastQuestion) {
            countAnswered++;
        }
    }
    return countAnswered == this->m_activePlayers;
}

void Game::ActAfterQuestionAnsweringEnded() {
    if (wasTheLastQuestion()) {
        MoveToGameResults();
    }
    else {
        moveToScoreBoard();
        std::thread([this]() {
            std::this_thread::sleep_for(std::chrono::seconds(getScoreShowingTime()));
            setNextQuestion();
            }).detach();
    }
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
    return m_questionTimeLimitSeconds;
}

void Game::timeCheckLoop()
{
    while (!m_stopTimeCheckThread.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Check every 100ms

        // Check if time limit has been exceeded
        auto elapsedTime = std::chrono::steady_clock::now() - m_lastQuestionStartTime;
        if (std::chrono::duration_cast<std::chrono::seconds>(elapsedTime).count() >= m_questionTimeLimitSeconds) {
            ActAfterQuestionAnsweringEnded();
        }
    }
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
