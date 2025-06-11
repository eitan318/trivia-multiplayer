#pragma once
#include "LoggedUser.hpp"
#include <map>
#include "Question.hpp"
#include <vector>

class Game {
public:
	Game(std::vector<Question> questions, std::vector<LoggedUser> players, unsigned int roomId, unsigned int questionTimeLimit);
	std::map<LoggedUser, Question> getPlayers();
	std::optional<Question> getQuestionForUser(const LoggedUser& user);
	unsigned int getQuestionTimeLimit() const;

	void removePlayer(const LoggedUser& user);
	unsigned int getId() const;
private:
	unsigned int m_questionTimeLimit;
	std::vector<Question> m_questions;
	std::map<LoggedUser, Question> m_players;
	int m_gameId;
};