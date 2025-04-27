#pragma once
#include "json.hpp"

/**
 * @enum ResponsesCodes
 * @brief Enumerates the response codes for different response types.
 */
enum ResponsesCodes : byte {
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
};

/**
 * @class Response
 * @brief Represents a general response.
 */
class Response {
public:
    unsigned int status;

    /**
     * @brief Default constructor for Response.
     */
    Response(unsigned int status) : status(status) {}

    Response() = delete;

    /**
     * @brief Gets the response code for this response.
     * @return The response code as an unsigned integer.
     */
    virtual byte getCode() const = 0;

    /**
     * @brief Converts the common fields of the response to a JSON object.
     * @return A JSON representation of the common response fields.
     */
    virtual nlohmann::json baseJson() const {
        return nlohmann::json{
            {"Status", status}
        };
    }

    /**
     * @brief Converts the response to a JSON object.
     * Derived classes should call `baseJson` to include common fields.
     * @return A JSON representation of the response.
     */
    virtual nlohmann::json getJson() const = 0;

    virtual ~Response() = default;
};
