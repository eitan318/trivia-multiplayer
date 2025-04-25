#pragma once
#include <string>
#include <vector>

/**
 * @class Question
 * @brief Represents a question with its difficulty, category, text, and possible answers.
 */
class Question
{
private:
    std::string m_question;              /**< The text of the question. */
    std::string m_difficulty;            /**< The difficulty level of the question. */
    int m_categoryId;                    /**< The category ID of the question. */
    std::vector<std::string> m_possibleAnswers; /**< The list of possible answers, with the correct answer at index 0. */

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
    Question(const std::string& difficulty, int categoryId, const std::string& question,
        const std::string& correctAnswer, const std::string& ans1, const std::string& ans2,
        const std::string& ans3)
        : m_difficulty(difficulty), m_categoryId(categoryId), m_question(question)
    {
        m_possibleAnswers.push_back(correctAnswer);
        m_possibleAnswers.push_back(ans1);
        m_possibleAnswers.push_back(ans2);
        m_possibleAnswers.push_back(ans3);
    }

    /**
     * @brief Gets the text of the question.
     * @return The question text as a string.
     */
    std::string getQuestion() {
        return m_question;
    }

    /**
     * @brief Gets the list of possible answers.
     * @return A vector of strings containing the possible answers.
     */
    std::vector<std::string> getPossibleAnswers() {
        return m_possibleAnswers;
    }

    /**
     * @brief Gets the index of the correct answer.
     * @return The index of the correct answer, always 0 in this implementation.
     */
    int getCorrectAnswerId() {
        return 0;  // Correct answer is always at index 0
    }
};
