#pragma once
#include "PersonalStatistics.hpp"

class PersonalStatisticsResponseData {
private:
	PersonalStatistics regularStats;
	PersonalStatistics stats1v1;

public:
	PersonalStatisticsResponseData(const PersonalStatistics& regular, const PersonalStatistics& stats1v1)
		: regularStats(regular), stats1v1(stats1v1) {
	}

	friend void to_json(nlohmann::json& j, const PersonalStatisticsResponseData& d) {
		j = nlohmann::json{
			{"RegularStats", d.regularStats},
			{"Stats1v1", d.stats1v1}
		};
	}
};