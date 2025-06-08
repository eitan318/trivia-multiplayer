#pragma once
#include <string>
#include <vector>
#include "json.hpp"

/**
 * @class Question
 * @brief Represents a question with its difficulty, category, text, and possible answers.
 */
class Question
{
private:
    std::string m_question;              /**< The text of the question. */
    std::string m_difficulty;            /**< The difficulty level of the question. */
    std::string m_category;                    /**< The category ID of the question. */
    std::vector<std::string> m_possibleAnswers; /**< The list of possible answers, with the correct answer at index 0. */
    int m_correctAnswerIdx;

public:
    /**
     * @brief Constructs a Question object.
     * @param difficulty The difficulty level of the question.
     * @param categoryId The category ID of the question.
     * @param question The text of the question.
     * @param correctAnswer The correct answer to the question.
     * @param ans1 An incorrect answer option.
     * @param ans2 An incorrect answer option.
     * @param ans3 An incorrect answer option.
     */
    Question(const std::string& difficulty, const std::string& category, const std::string& question,
        const std::string& correctAnswer, const std::string& ans1, const std::string& ans2,
        const std::string& ans3);

    /**
     * @brief Gets the text of the question.
     * @return The question text as a string.
     */
    std::string getQuestion() const;

    /**
     * @brief Gets the list of possible answers.
     * @return A vector of strings containing the possible answers.
     */
    std::vector<std::string> getPossibleAnswers() const;

    /**
     * @brief Gets the index of the correct answer.
     * @return The index of the correct answer, always 0 in this implementation.
     */
    int getCorrectAnswerId() const;

    /**
     * @brief Serializes the Question object to JSON.
     * @param j The JSON object to populate.
     * @param q The Question object to serialize.
     */
    friend void to_json(nlohmann::json& j, const Question& q);
};

/**
 * @brief Serializes the Question object to JSON.
 * @param j The JSON object to populate.
 * @param q The Question object to serialize.
 */
inline void to_json(nlohmann::json& j, const Question& q) {
    j = nlohmann::json{
        {"difficulty", q.m_difficulty},
        {"category", q.m_category},   
        {"question", q.m_question},
        {"possibleAnswers", q.m_possibleAnswers},
    };
}
