#include "StatisticsManager.h"

StatisticsManager& StatisticsManager::getInstance(IDatabase& database)
{
    static StatisticsManager instance(database);
    return instance;
}

std::list<HighScoreInfo> StatisticsManager::getBestScores(int limit)
{
    return this->m_db->getBestScores(limit);
}

PersonalStatistics StatisticsManager::getPlayerStatistics(const std::string& username)
{
    return PersonalStatistics(
        username,
        this->m_db->getNumOfTotalCorrectAnswers(username),
        this->m_db->getNumOfTotalAnswers(username),
        this->m_db->getNumOfPlayerGames(username),
        this->m_db->getAvgAnswerTime(username));
}
