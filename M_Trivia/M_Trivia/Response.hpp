#pragma once
#include "IResponseErrors.hpp"
#include "json.hpp"

/**
 * @enum ResponseCodes
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
	C_HighScoresRespones = 12,
	C_VerifyPasswordResetCodeResponse = 13,
	C_StartGameResponse = 14,
	C_LeaveRoomResponse = 15,
	C_GetRoomStatusResponse = 16,
	C_CloseRoomResponse = 17,
	C_GetQuestionResponse = 18,
	C_LeaveGameResponse = 19,
	C_GetGameResultsResponse = 20,
	C_SubmitAnswerResponse = 21,
	C_GetRoomStateResponse = 22,



};





#define GENERAL_SUCCESS_RESPONSE_STATUS 0

template<ResponseCodes Code, typename ErrorType = IResponseErrors>
class Response {
private:
    std::unique_ptr<ErrorType> errors; // Use unique_ptr for better ownership semantics
    unsigned int status;

public:
    /**
     * @brief Constructor for Response with errors.
     * @param errors The error object containing details of the response.
     */
    explicit Response(std::unique_ptr<ErrorType> errors)
        : errors(std::move(errors)), status(this->errors ? this->errors->statusCode() : GENERAL_SUCCESS_RESPONSE_STATUS) {
    }

    /**
     * @brief Constructor for Response with status only.
     * @param status The status code of the response.
     */
    explicit Response(unsigned int status)
        : errors(nullptr), status(status) {
    }

    // Delete default constructor to enforce proper initialization.
    Response() = delete;

    /**
     * @brief Gets the response code for this response.
     * @return The response code as specified by the template parameter.
     */
    ResponseCodes getCode() const {
        return Code;
    }

    /**
     * @brief Converts the response to a JSON object.
     * @return A JSON representation of the response.
     */
    virtual nlohmann::json getJson() const {
        nlohmann::json errorsJson = errors ? errors->getJson() : nlohmann::json();
        nlohmann::json j = nlohmann::json{
            {"Status", status},
        };
        if (errors) {
            j["Errors"] = errorsJson;
        }
        return j;
    }
};

#include "LoginResponseErrors.hpp"
#include "SignupResponseErrors.hpp"
#include "PasswordCodeResponseErrors.hpp"
#include "ResetPasswordResponseErrors.hpp"
#include "CreateRoomResponseErrors.hpp"
#include "GeneralResponseErrors.hpp"

using CloseRoomResponse = Response<ResponseCodes::C_CloseRoomResponse, GeneralResponseErrors>;
using StartGameResponse = Response<ResponseCodes::C_StartGameResponse, GeneralResponseErrors>;
using LeaveRoomResponse = Response<ResponseCodes::C_LeaveRoomResponse, IResponseErrors>;
using LeaveGameResponse = Response<ResponseCodes::C_LeaveGameResponse, GeneralResponseErrors>;
using LogoutResponse = Response<ResponseCodes::C_LogoutResponse, IResponseErrors>;
using LoginResponse = Response<ResponseCodes::C_LoginResponse, LoginResponseErrors>;
using SignupResponse = Response<ResponseCodes::C_SignupResponse, SignupResponseErrors>;
using PasswordCodeResponse = Response<ResponseCodes::C_SendPasswordResetCodeResponse, PasswordCodeResponseErrors>;
using ResetPasswordResponse = Response<ResponseCodes::C_ResetPasswordResponse, ResetPasswordResponseErrors>;
using JoinRoomResponse = Response<ResponseCodes::C_JoinRoomResponse, GeneralResponseErrors>;


