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
=======
    for (auto& [user, data] : this->m_players) {
        if (data.currentQuestion == this->m_questions.) {
>>>>>>> f605d58875001ef24f822cf19100f8f066a63174
            data.correctAnswerCount++;
        }
        else 
        {
            data.wrongAnswerCount++;
        }
<<<<<<< HEAD
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