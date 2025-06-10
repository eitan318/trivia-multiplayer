#include "Game.hpp"

Question Game::getQuestionForUser(LoggedUser user) 
{
    if (m_players.find(user) == m_players.end()) {
        throw std::invalid_argument("User not found in game.");
    }
    GameData& data = m_players[user];
    return data.currentQuestion;

}
void Game::submitAnswer() 
{
    /*for (auto& [user, data] : this->m_players) {
        if (data.currentQuestion == this->m_questions) {
            data.correctAnswerCount++;
        }
        else 
        {
            data.wrongAnswerCount++;
        }
    }*/
}
void Game::removePlayer()
{
    //
}

void Game::sumitGameStatsToDB(GameData gameData) 
{
    //
}