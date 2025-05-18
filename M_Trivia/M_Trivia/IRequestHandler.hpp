#pragma once
#include "RequestInfo.hpp"
#include "RequestResult.hpp"

/**
 * @interface IRequestHandler
 * @brief An interface for handling incoming requests.
 *
 * The IRequestHandler interface defines the contract for any request handler.
 * Any class that implements this interface should be able to determine whether
 * a given request is relevant and how to process that request.
 */
class IRequestHandler {
public:
  virtual ~IRequestHandler() {};

  /**
   * @brief Determines whether the given request is relevant to this handler.
   *
   * This function is used to check if the handler should process the given
   * request based on the request's attributes (e.g., request code).
   *
   * @param requestInfo The request to check for relevance.
   * @return `true` if the request is relevant, `false` otherwise.
   */
  virtual bool isRequestRelevant(const RequestInfo &) const = 0;

  /**
   * @brief Handles the given request and produces a result.
   *
   * This function processes the provided request and generates the
   * corresponding response. The response will be encapsulated in a
   * RequestResult object.
   *
   * @param requestInfo The request to process.
   * @return A RequestResult that encapsulates the response and any additional
   * information.
   */
  virtual RequestResult handleRequest(const RequestInfo &) = 0;
};
