#pragma once 
#include "Question.hpp"
#include "json.hpp"
struct GetQuestionResponseData
{
	Question question;
	unsigned int questionNumber;

	friend void to_json(nlohmann::json& j, const GetQuestionResponseData& d) {
		j = nlohmann::json{
			{"Question", d.question},
	{"QuestionNumber", d.questionNumber}
		};
	}
};