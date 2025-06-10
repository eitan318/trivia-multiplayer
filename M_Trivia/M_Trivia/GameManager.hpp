#pragma once
#include "IDatabase.hpp"
#include "vector"
#include "Game.hpp"
#include "Room.hpp"

class GameManager {
public:
	Game createGame(Room room);
	void deleteGame(int gameId);
private:

};