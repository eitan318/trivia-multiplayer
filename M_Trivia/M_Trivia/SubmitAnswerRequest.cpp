#include "SubmitAnswerRequest.hpp"

SubmitAnswerRequest::SubmitAnswerRequest(const nlohmann::json& j) : correctAnswerId(j.at("CorrectAnswerID")) 
{
}

const unsigned int SubmitAnswerRequest::getAnswerId() const
{
	return correctAnswerId;
}
