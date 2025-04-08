#pragma once
#include "IDatabase.h"
#include "PlayerStatistics.hpp"
#include <list>



class StatisticsManager
{
private:
	IDatabase* m_db;
	StatisticsManager(IDatabase& database);
	~StatisticsManager() = default;
	StatisticsManager(const StatisticsManager&) = delete;
	StatisticsManager& operator=(const StatisticsManager&) = delete;
public:
	static StatisticsManager& getInstance(IDatabase& database);
	std::list<HighScoreInfo> getBestScores(int limit);
	PlayerStatistics getPlayerStatistics(const std::string& username);
};

