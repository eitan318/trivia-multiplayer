#include "IRequestHandler.h"

bool IRequestHandler::isRequestRelevant(const RequestInfo&)
{
    return false;
}

RequestResult IRequestHandler::handleRequest(const RequestInfo&)
{
    return RequestResult();
}
