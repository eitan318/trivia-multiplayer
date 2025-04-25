#pragma once
#include <vector>
#include <string>
#include "IRequestHandler.h"

struct IRequestHandler;

/**
 * @struct RequestResult
 * @brief response and the next handler
 */
struct RequestResult {
    std::vector<char> response;
    IRequestHandler* newHandler = nullptr; 
};
