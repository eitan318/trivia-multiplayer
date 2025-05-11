#pragma once
#include <vector>
#include <memory>

class IRequestHandler;

/**
 * @struct RequestResult
 * @brief response and the next handler
 */
class RequestResult {
public:
    RequestResult(const std::vector<char>& response, std::unique_ptr<IRequestHandler> newHandler) :
        response(response), newHandler(std::move(newHandler)) {

    }
    RequestResult() {};
    std::vector<char> response;
    std::unique_ptr<IRequestHandler> newHandler; 
};
