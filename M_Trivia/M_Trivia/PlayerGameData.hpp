#pragma once
#include <chrono>

class PlayerGameData {
public:
    Question question;

    bool answeredLastQuestion;

    PlayerGameData() = default;
    PlayerGameData(const Question& q)
        : question(q), answeredLastQuestion(false) 
    {
    }
};
