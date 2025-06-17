#include "GetGameStateResponse.hpp"

GetGameStateResponse::GetGameStateResponse(unsigned int status, const GameStatus gameStatus) : Response(status), m_gameStatus(gameStatus)
{
}

nlohmann::json GetGameStateResponse::getJson() const
{
	nlohmann::json j = Response::getJson();
	j["GameStatus"] = this->m_gameStatus;
	return j;
}
