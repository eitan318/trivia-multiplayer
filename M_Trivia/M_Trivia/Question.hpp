#pragma once
#include <string>
#include <vector>

class Question
{
private:
    std::string m_question;
    std::string m_difficulty;
    int m_categoryId;
    std::vector<std::string> m_possibleAnswers;

public:
    // Constructor
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

    std::string getQuestion() {
        return m_question;
    }

    std::vector<std::string> getPossibleAnswers() {
        return m_possibleAnswers;
    }

    int getCorrectAnswerId() {
        return 0;  // Correct answer is always at index 0
    }
};
