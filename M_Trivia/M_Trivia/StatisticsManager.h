#pragma once
#include "IDatabase.h"
#include "PersonalStatistics.hpp"
#include <vector>



class StatisticsManager
{
private:
	IDatabase* m_db;
	StatisticsManager(IDatabase& database) : m_db(&database) {};
	~StatisticsManager() = default;
	StatisticsManager(const StatisticsManager&) = delete;
	StatisticsManager& operator=(const StatisticsManager&) = delete;
public:
	static StatisticsManager& getInstance(IDatabase& database);
	std::vector<HighScoreInfo> getBestScores(int limit);
	PersonalStatistics getPlayerStatistics(const std::string& username);
};

