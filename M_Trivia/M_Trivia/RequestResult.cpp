#include "RequestResult.hpp"
#include "IRequestHandler.hpp"

RequestResult::RequestResult(const std::vector<char>& response, std::shared_ptr<IRequestHandler> newHandler) :
    response(response), newHandler(std::move(newHandler)) {

}

RequestResult::RequestResult()
{
}
