#pragma once
#include <vector>
#include <memory>

class IRequestHandler;

/**
 * @struct RequestResult
 * @brief response and the next handler
 */
struct RequestResult {
    std::vector<char> response;
    std::unique_ptr<IRequestHandler> newHandler; 
};
