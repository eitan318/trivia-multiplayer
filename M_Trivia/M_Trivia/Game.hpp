#pragma once
#include "GameData.hpp"
#include "LoggedUser.hpp"
#include <map>

class Game {
public:
	std::map<LoggedUser, GameData> getPlayers();
	Question getQuestionForUser(LoggedUser user);
	void submitAnswer();
	void removePlayer();
private:
	void sumitGameStatsToDB(GameData gameData);

	std::vector<Question> m_questions;
	std::map<LoggedUser, GameData> m_players;
	int m_gameId;
};