#include "StatisticsManager.hpp"

StatisticsManager& StatisticsManager::getInstance(IDatabase& database)
{
	static StatisticsManager instance(database);
	return instance;
}

std::vector<HighScoreInfo> StatisticsManager::getBestScores(int limit) const
{
	return this->m_db.getBestScores(limit, false);
}

PersonalStatistics StatisticsManager::getPlayerStatistics(const std::string& username, bool in1v1Game) const
{
	return this->m_db.getPersonalStatistics(username, in1v1Game);
}
