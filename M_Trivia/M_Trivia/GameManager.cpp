#include "GameManager.hpp"

GameManager::GameManager(IDatabase& dataBase) : m_database(dataBase) {
    m_timeoutThread = std::thread(&GameManager::timeoutCheckLoop, this);
}

GameManager& GameManager::getInstance(IDatabase& database) {
    static GameManager instance(database);
    return instance;
}

void GameManager::timeoutCheckLoop()
{
    while (!m_stopTimeoutThread.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(300)); // Check every 300ms

        for (const auto& [id, game] : this->m_gamesByRoomId) {
            if (game->reachedTimeout()) {
                game->actAfterQuestionAnsweringEnded();
            }
            if (game->reachedTimeout()) {
                for (const auto& [player, playerData] : game->getPlayers()) {
                    if (!playerData.answeredLastQuestion) {
                        submitAnswer(player, game, -1); // Submit default answer
                    }
                }
            }
        }
        
    }
}

void GameManager::handleTimeout(std::shared_ptr<Game> game) {

}


std::shared_ptr<Game> GameManager::createGame(Room* room)
{
    std::lock_guard<std::mutex> lock(m_gamesMutex); 
    std::vector<Question> questions = this->m_database.getQuestions(room->getRoomPreview().roomData.numOfQuestionsInGame);
    unsigned int gameId = this->m_database.createGame(room->getRoomPreview().roomData.name, std::time(nullptr));
    std::shared_ptr<Game> game = std::make_shared<Game>(questions, room->getUsersVector(), gameId, room->getRoomPreview().roomData.timePerQuestion, room);
    this->m_gamesByRoomId[room->getId()] = game;
    return game;
}

void GameManager::deleteGame(int gameId)
{
    std::lock_guard<std::mutex> lock(m_gamesMutex);
    this->m_gamesByRoomId.erase(gameId);
}

std::shared_ptr<Game> GameManager::getGame(unsigned int gameId)
{
    std::lock_guard<std::mutex> lock(m_gamesMutex);
    return this->m_gamesByRoomId[gameId];
}

GeneralResponseErrors GameManager::submitAnswer(const LoggedUser& user, std::shared_ptr<Game> game,
    int answerId)
{
    std::optional<Question> originalQuestionAnswered = game->getQuestionForUser(user);
    game->userAnswered(user);

    GeneralResponseErrors errors;
    if (!originalQuestionAnswered.has_value()) {
        errors.generalError = "User not in game.";
    }
    Question q = originalQuestionAnswered.value();
    
    int answerOriginalNumber = answerId == -1 ? -1 : q.getOriginalAnswerNum(answerId);
    bool isCorrect = q.getCorrectAnswerId() == answerId;
    double answerTime = game->getAnswerDouration(std::chrono::steady_clock::now());
    double  timeLimit = game->getQuestionTimeLimit();
    if (answerTime > timeLimit + 1)
        errors.generalError = "Time problem overflow occured.";

    if (answerTime >= timeLimit) {
        answerTime = timeLimit;
    }
    int score = answerId == -1 ? 0 : calcAnswerScore(q.getDifficultyLevel(), answerTime, isCorrect, timeLimit);
    this->m_database.addUserAnswer(user.getUsername(), game->getId(), q.getId(), 
        answerOriginalNumber, score, answerTime);

    if (game->didEveryActiveAnswered()) {
        game->actAfterQuestionAnsweringEnded();
    }
    return errors;
}

std::vector<PlayerResults> GameManager::getGameResults(std::shared_ptr<Game> game) const
{
    std::vector<PlayerResults> playersResults;

    auto players = game->getPlayers();
    for (const auto& [player, _] : players) {
        std::optional<PlayerResults> playerResults = this->m_database.getPlayerResults(player.getUsername(), game->getId());
        if (playerResults.has_value()) {
            playersResults.emplace_back(playerResults.value());
        }
    }
    std::sort(playersResults.begin(), playersResults.end(), [](const PlayerResults& a, const PlayerResults& b) {
        return a.score > b.score;
        });
    return playersResults;
}

int GameManager::calcAnswerScore(QuestionDifficultyLevelScores diffLevel, double answerTime, bool isCurrect, double timeLimit) const
{
    double precentFromMaxScore = 1 - (answerTime / timeLimit) / 2.0;
    unsigned int maxAnsScore = diffLevel;
    return isCurrect ? maxAnsScore * precentFromMaxScore : 0;
}

GameManager::~GameManager()
{
    {
        std::lock_guard<std::mutex> lock(m_gamesMutex);
        m_gamesByRoomId.clear();
    }

    m_stopTimeoutThread.store(true);
    if (m_timeoutThread.joinable()) {
        m_timeoutThread.join();
    }
}
