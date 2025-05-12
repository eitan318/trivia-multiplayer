#include "StatisticsManager.h"

StatisticsManager& StatisticsManager::getInstance(IDatabase& database)
{
	static StatisticsManager instance(database);
	return instance;
}

std::vector<HighScoreInfo> StatisticsManager::getBestScores(int limit) const
{
	return this->m_db.getBestScores(limit);
}

PersonalStatistics StatisticsManager::getPlayerStatistics(const std::string& username) const
{
	return PersonalStatistics(
		username,
		this->m_db.getNumOfTotalCorrectAnswers(username),
		this->m_db.getNumOfTotalAnswers(username),
		this->m_db.getNumOfPlayerGames(username),
		this->m_db.getAvgAnswerTime(username));
}
