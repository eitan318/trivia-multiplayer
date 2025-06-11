#pragma once
#include "IDatabase.hpp"
#include "vector"
#include "Game.hpp"
#include "Room.hpp"
#include "GeneralResponseErrors.hpp"
#include "PlayerResults.hpp"

class GameManager {
public:
	static GameManager& getInstance(IDatabase& database);

	std::shared_ptr<Game> createGame(Room* room);
	void deleteGame(int gameId);
	GeneralResponseErrors submitAnswer(const LoggedUser& user, std::shared_ptr<Game> game, unsigned int answerId);
	std::vector<PlayerResults> getGameResults(std::shared_ptr<Game> game) const;

	~GameManager();
private:
	GameManager(IDatabase& dataBase);
	int calcAnswerScore(QuestionDifficultyLevelScores diffLevel, double answerTime, bool isCurrect, double timeLimit) const;
	std::map<unsigned int, std::shared_ptr<Game>> m_games;
	IDatabase& m_database;
};