#include "SubmitAnswerRequest.hpp"

SubmitAnswerRequest::SubmitAnswerRequest(const nlohmann::json& j) {
	const unsigned int answerid = j.at("AnswerID");

	this->answerId = answerid;
}

const unsigned int SubmitAnswerRequest::getAnswerId() const
{
	return answerId;
}
