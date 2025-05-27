#include "GetRoomStateResponse.hpp"

GetRoomStateResponse::GetRoomStateResponse(unsigned int status,
	bool hasGameBegun,
	const std::vector<std::string>& players,
	unsigned int answerCount,
	double answerTimeOut) : Response(status),  m_hasGameBegun(hasGameBegun),
	m_players(players),
	m_answerCount(answerCount),
	m_answerTimeOut(answerTimeOut)
{
}

ResponseCodes GetRoomStateResponse::getCode() const
{
	return ResponseCodes::C_GetRoomStateResponse;
}

nlohmann::json GetRoomStateResponse::getJson() const
{
	nlohmann::json j = Response::getJson();
	j["Players"] = m_players;
	j["AnswerCount"] = m_answerCount;
	j["HasGameBegun"] = m_hasGameBegun;
	j["AnswerTimeOut"] = m_answerTimeOut;
	return j;
}



