#include "QuestionRecord.hpp"

QuestionRecord::QuestionRecord(const std::string question,
	const std::string diffLevel,
	const std::string rightAnswer,
	const std::vector<std::string> wrongAnswers,
	std::string category) : m_question(question), m_diffLevel(diffLevel),
	m_rightAnswer(rightAnswer), m_wrongAnswers(wrongAnswers), m_category(category)
{}

QuestionRecord::QuestionRecord(const QuestionRecord& other) {
	m_question = other.m_question;
	m_diffLevel = other.m_diffLevel;
	m_wrongAnswers = other.m_wrongAnswers;
	m_rightAnswer = other.m_rightAnswer;
	m_category = other.m_category;
}

std::string QuestionRecord::getQuestion() {
	return m_question;
}

std::string QuestionRecord::getDifficultyLevel() {
	return m_diffLevel;
}

std::vector<std::string> QuestionRecord::getWrongAnswers() {
	return m_wrongAnswers;
}

std::string QuestionRecord::getRightAnswer() {
	return m_rightAnswer;
}

std::string QuestionRecord::getCategory() {
	return m_category;
}