#include "GameManager.hpp"

std::shared_ptr<Game> GameManager::createGame(Room* room)
{

    std::vector<Question> questions = this->m_database.getQuestions(10);
    unsigned int gameId = this->m_database.createGame();
    std::shared_ptr<Game> game = std::make_shared<Game>(questions, room->getUsersVector(), gameId, room->getRoomPreview().roomData.timePerQuestion);
    this->m_games[gameId] = game;
    return game;
}

void GameManager::deleteGame(int gameId)
{
    this->m_games.erase(gameId);
}

GameManager::GameManager(IDatabase& dataBase) : m_database(dataBase)
{
    
}

GameManager& GameManager::getInstance(IDatabase& database) {
    static GameManager instance(database);
    return instance;
}





GeneralResponseErrors GameManager::submitAnswer(const LoggedUser& user, std::shared_ptr<Game> game,  unsigned int answerId)
{
    std::optional<Question> oq = game->getQuestionForUser(user);
    GeneralResponseErrors errors;
    if (!oq.has_value()) {   
        errors.generalError = "User not in game.";
    }
    Question q = oq.value();

    bool isCorrect = q.getCorrectAnswerId() == answerId;
    double ansTime = 0;
    int score = calcAnswerScore(q.getDifficultyLevel(), ansTime, isCorrect, game->getQuestionTimeLimit());
    this->m_database.addUserAnswer(user.getUsername(), game->getId(), q.getId(), isCorrect, score, ansTime);

    errors.statusCode = !errors.noErrors();

    return errors;
}

std::vector<PlayerResults> GameManager::getGameResults(std::shared_ptr<Game> game) const
{
    std::vector <PlayerResults> playersResults;
    for (auto it = game->getPlayers().begin(); it != game->getPlayers().end(); it++) {
        LoggedUser player = it->first;
        std::optional<PlayerResults> playerResults = this->m_database.getPlayerResults(player.getUsername(), game->getId());
        if (playerResults.has_value()) {
            playersResults.emplace_back(playerResults.value());
        }
    }
    return playersResults;
}


int GameManager::calcAnswerScore(QuestionDifficultyLevelScores diffLevel, double answerTime, bool isCurrect, double timeLimit) const{

    unsigned int maxAnsScore = diffLevel;
    return isCurrect ? maxAnsScore * (0.5 + answerTime / timeLimit) : 0;
}


GameManager::~GameManager()
{
}

