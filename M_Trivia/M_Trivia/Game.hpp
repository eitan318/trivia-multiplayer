#pragma once
#include "LoggedUser.hpp"
#include <map>
#include "Question.hpp"
#include "PlayerGameData.hpp"
#include <vector>

class Game {
public:
	Game(std::vector<Question> questions, std::vector<LoggedUser> players, unsigned int roomId, unsigned int questionTimeLimit);
	std::map<LoggedUser, PlayerGameData> getPlayers();
	std::optional<Question> getQuestionForUser(const LoggedUser& user);
    void setNextQuestionForUser(const LoggedUser& user);
	unsigned int getQuestionTimeLimit() const;
	bool userExistsInGame(const LoggedUser& user) const;

	void removePlayer(const LoggedUser& user);
	unsigned int getId() const;
private:
	unsigned int m_questionTimeLimit;
	std::vector<Question> m_questions;
	//Player to question idx
	std::map<LoggedUser, PlayerGameData> m_players;
	int m_gameId;
};