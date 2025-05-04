#pragma once
#include <vector>
#include "IRequestHandler.h"
#include <memory>

struct IRequestHandler;

/**
 * @struct RequestResult
 * @brief response and the next handler
 */
struct RequestResult {
    std::vector<char> response;
    std::unique_ptr<IRequestHandler> newHandler; 
};
