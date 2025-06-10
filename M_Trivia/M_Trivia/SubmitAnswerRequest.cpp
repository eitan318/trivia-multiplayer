#include "SubmitAnswerRequest.hpp"

SubmitAnswerRequest::SubmitAnswerRequest(const nlohmann::json& j) {
	const unsigned int correctAnswerid = j.at("CorrectAnswerID");

	this->correctAnswerId = correctAnswerid;
}

const unsigned int SubmitAnswerRequest::getAnswerId() const
{
	return correctAnswerId;
}
