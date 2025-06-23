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
                handleTimeout(game);
            }
        }
        
    }
}

void GameManager::handleTimeout(std::shared_ptr<Game> game) {
    //Only if this wasnt called before by timeout
    if (game->getStatus() != GameStatus::AnsweringQuestion)
        return;

    for (const auto& [player, playerData] : game->getPlayers()) {
        if (!playerData.answeredLastQuestion) {
            submitAnswer(player, game, -1); // Submit default answer
        }
    }
    actAfterQuestionAnsweringEnded(game);

}

void GameManager::leaveGame(std::shared_ptr<Game> game, std::shared_ptr<RoomPreview> roomPreview, const LoggedUser& user)
{
    game->playerDeactivate(user);
    if (game->countActivePlayers() == 0) {
        roomPreview->closeGame();
        deleteGame(roomPreview->roomData.id);
    }
}


std::shared_ptr<Game> GameManager::createGame(std::shared_ptr<RoomPreview> roomPreview)
{
    std::lock_guard<std::mutex> lock(m_gamesMutex); 
    std::vector<Question> questions = this->m_database.getRandQuestions(roomPreview->roomData.numOfQuestionsInGame);
    unsigned int gameId = this->m_database.createGame(roomPreview->roomData.name, std::time(nullptr));
    std::shared_ptr<Game> game = std::make_shared<Game>(questions, roomPreview, gameId);

    this->m_gamesByRoomId[roomPreview->roomData.id] = game;
    return game;
}


void GameManager::deleteGame(int roomId)
{
    std::lock_guard<std::mutex> lock(m_gamesMutex);
    this->m_gamesByRoomId.erase(roomId);
}

std::shared_ptr<Game> GameManager::getGame(unsigned int roomId)
{
    std::lock_guard<std::mutex> lock(m_gamesMutex);
    return this->m_gamesByRoomId[roomId];
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
        this->actAfterQuestionAnsweringEnded(game);
    }
    return errors;
}

std::vector<PlayerResults> GameManager::getGameResults(std::shared_ptr<Game> game) const
{
    std::vector<PlayerResults> playersResults;

    auto players = game->getPlayers();
    for (const auto& [player, _] : players) {
        std::optional<PlayerResults> playerResults = this->m_database.getPlayerResults(player.getUsername(), game->getId(), game->getQuestionsAmount());
        if (playerResults.has_value()) {
            playersResults.emplace_back(playerResults.value());
        }
    }
    std::sort(playersResults.begin(), playersResults.end(), [](const PlayerResults& a, const PlayerResults& b) {
        return a.score > b.score;
        });
    return playersResults;
}

void GameManager::actAfterQuestionAnsweringEnded(std::shared_ptr<Game> game) {
    //Only if this wasnt called before by timeout
    if (game->getStatus() != GameStatus::AnsweringQuestion)
        return;


    if (game->wasTheLastQuestion()) {
        game->moveToGameResults();
    }
    else {
        game->moveToScoreBoard();
        std::thread([game]() {
            std::this_thread::sleep_for(std::chrono::seconds(game->getScoreShowingTime()));
            game->setNextQuestion();
            }).detach();
    }
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
