#pragma once
#include <chrono>

class PlayerGameData {
public:
    Question question;

    bool answeredLastQuestion;

    PlayerGameData() = default;
    PlayerGameData(const Question& q, std::chrono::time_point<std::chrono::steady_clock> startTime)
        : question(q), answeredLastQuestion(false) 
    {
    }
};
