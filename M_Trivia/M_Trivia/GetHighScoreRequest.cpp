#include "GetHighScoreRequest.hpp"

GetHighScoreRequest::GetHighScoreRequest(const nlohmann::json &j)
    : topPlayersLimit(j.at("TopPlayersLimit")) {}

unsigned int GetHighScoreRequest::getTopPlayersLimit() const {
  return topPlayersLimit;
}
