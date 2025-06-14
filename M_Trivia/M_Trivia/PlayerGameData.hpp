#pragma once
#include <time.h>


class PlayerGameData {
public:
    unsigned int questionIdx = 0;
    Question question;
    time_t lastStartTime = 0;

    PlayerGameData() = default; // Default constructor
    PlayerGameData(unsigned int idx, const Question& q, time_t startTime)
        : questionIdx(idx), question(q), lastStartTime(startTime) {
    }
};

