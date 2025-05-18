#pragma once
#include "IResponseErrors.hpp"
#include "json.hpp"
#include <memory>

/**
 * @enum ResponsesCodes
 * @brief Enumerates the response codes for different response types.
 */
enum class ResponseCodes : unsigned char {
  C_ErrorResponse = 0,
  C_LoginResponse = 1,
  C_GetRoomsResponse = 2,
  C_GetPlayersInRoomResponse = 3,
  C_GetHighScoreResponse = 4,
  C_GetPersonalStatsResponse = 5,
  C_SendPasswordResetCodeResponse = 6,
  C_SignupResponse = 7,
  C_ResetPasswordResponse = 8,
  C_JoinRoomResponse = 9,
  C_CreateRoomResponse = 10,
  C_LogoutResponse = 11,
  C_VerifyPasswordResetCodeResponse = 12,
};

class Response {
private:
  IResponseErrors *errors;
  unsigned int status;

public:
  /**
   * @brief Virtual destructor for the Response class.
   */
  virtual ~Response() = default;
  /**
   * @brief Constructor for Response.
   * @param errors The error object containing details of the response.
   */
  explicit Response(IResponseErrors *errors);

  /**
   * @brief Constructor for Response with status only.
   * @param status The status code of the response.
   */
  explicit Response(unsigned int status);

  // Delete default constructor to enforce proper initialization.
  Response() = delete;

  /**
   * @brief Gets the response code for this response.
   * @return The response code as a byte (uint8_t).
   */
  virtual ResponseCodes getCode() const = 0;

  /**
   * @brief Converts the response to a JSON object.
   * @return A JSON representation of the response.
   */
  virtual nlohmann::json getJson() const;
};
