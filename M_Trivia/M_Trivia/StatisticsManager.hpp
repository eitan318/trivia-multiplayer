#pragma once
#include "IDatabase.hpp"
#include "PersonalStatistics.hpp"
#include "HighScoreInfo.hpp"
#include <vector>

/**
 * @brief Handles statistical data and metrics for users.
 */
class StatisticsManager
{
private:
    IDatabase& m_db; ///< Pointer to the database interface for accessing statistics.

    /**
     * @brief Constructs a StatisticsManager instance.
     * @param database Reference to the database interface.
     */
    StatisticsManager(IDatabase& database) : m_db(database) {};

    /**
     * @brief Default destructor.
     */
    ~StatisticsManager() = default;

    // Disable copy constructor and assignment operator to enforce singleton pattern.
    StatisticsManager(const StatisticsManager&) = delete;
    StatisticsManager& operator=(const StatisticsManager&) = delete;

public:
    /**
     * @brief Retrieves the singleton instance of StatisticsManager.
     * @param database Reference to the database interface.
     * @return A reference to the StatisticsManager instance.
     */
    static StatisticsManager& getInstance(IDatabase& database);

    /**
     * @brief Retrieves the top scores from the database.
     * @param limit The maximum number of high scores to retrieve.
     * @return A vector of HighScoreInfo objects representing the top scores.
     */
    std::vector<HighScoreInfo> getBestScores(int limit) const;

    /**
     * @brief Retrieves personal statistics for a specific player.
     * @param username The username of the player.
     * @return A PersonalStatistics object containing the player's statistics.
     */
    PersonalStatistics getPlayerStatistics(const std::string& username) const;
};
