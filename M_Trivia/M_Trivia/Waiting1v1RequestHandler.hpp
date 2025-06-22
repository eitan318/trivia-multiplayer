#pragma once
#include "IRequestHandler.hpp"
#include "RequestHandlerFactory.hpp"
#include "LoggedUser.hpp"
#include "Waiting1v1Manager.hpp"


class Waiting1v1RequestHandler : public IRequestHandler, public std::enable_shared_from_this<Waiting1v1RequestHandler> {
public:
    Waiting1v1RequestHandler(RequestHandlerFactory& handlerFactory, const LoggedUser& user);
    
    ~Waiting1v1RequestHandler();
    /**
     * @brief Checks if a given request is relevant for this handler.
     * @param requestInfo The request information.
     * @return True if the request is relevant, otherwise false.
     */
    bool isRequestRelevant(const RequestInfo & requestInfo) const override;

    /**
     * @brief Handles a request and routes it to the appropriate method.
     * @param requestInfo The request information.
     * @return A RequestResult containing the serialized response and the next
     * handler.
     */
    RequestResult handleRequest(const RequestInfo & requestInfo) override;

    void Cleanup() override;

private:
    RequestResult leave1v1WaitingRoom(const RequestInfo& requestInfo);
    RequestResult didFoundMatch(const RequestInfo& requestInfo);
    RequestHandlerFactory& m_handlerFactory;
    LoggedUser m_user;
    Waiting1v1Manager& m_waiting1v1Manager;

};