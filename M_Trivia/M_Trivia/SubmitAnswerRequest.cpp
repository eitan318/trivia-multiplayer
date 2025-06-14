#include "SubmitAnswerRequest.hpp"

SubmitAnswerRequest::SubmitAnswerRequest(const nlohmann::json& j) : m_chosenAnswerId(j.at("ChosenAnswerId")) 
{
}

const int SubmitAnswerRequest::getAnswerId() const
{
	return m_chosenAnswerId;
}
