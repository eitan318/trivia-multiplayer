#pragma once
#include <string>
#include "QuestionDificultyLevel.h"
#include "json.hpp"
#include <vector>


class QuestionRecord {
public:
	QuestionRecord(const std::string question,
		const std::string diffLevel,
		const std::string rightAnswer,
		const std::vector<std::string> wrongAnswers,
		std::string category);

	QuestionRecord(const QuestionRecord& other);

	QuestionRecord() = default;

	std::string getQuestion();

	std::string getDifficultyLevel();
	
	std::vector<std::string> getWrongAnswers();

	std::string getRightAnswer();

	std::string getCategory();
private:

	std::string m_question;
	std::string m_diffLevel; //Easy - Medium - Hard
	std::vector<std::string> m_wrongAnswers;
	std::string m_rightAnswer;
	std::string m_category;
	
	/**
		 * @brief Serializes the Question object to JSON.
		 * @param j The JSON object to populate.
		 * @param q The Question object to serialize.
		 */
	friend void to_json(nlohmann::json& j, const QuestionRecord& q);
	
	inline void from_json(const nlohmann::json& j, QuestionRecord& q);

};

/**
 * @brief Serializes the Question object to JSON.
 * @param j The JSON object to populate.
 * @param q The Question object to serialize.
 */
inline void to_json(nlohmann::json& j, const QuestionRecord& q) {
	j = nlohmann::json{
		{"Question", q.m_question},
		{"DifficultyLevel", q.m_diffLevel},
		{"WrongAnswers", q.m_wrongAnswers},
		{"RightAnswer", q.m_rightAnswer},
		{"Category", q.m_category},
	};
}

inline void from_json(const nlohmann::json& j, QuestionRecord& q) {
	q = QuestionRecord(
		j.at("Question").get<std::string>(),
		j.at("DifficultyLevel").get<std::string>(),
		j.at("RightAnswer").get<std::string>(),
		j.at("WrongAnswers").get<std::vector<std::string>>(),
		j.at("Category").get<std::string>()
	);
}
