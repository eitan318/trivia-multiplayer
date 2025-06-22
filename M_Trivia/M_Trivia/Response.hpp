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
    C_GetGameStateResponse = 23,
    C_Leave1v1WaitingListResponse = 24,
    C_DidFound1v1MatchResponse = 25,
};

#define GENERAL_SUCCESS_RESPONSE_STATUS 0

template<ResponseCodes Code, typename ErrorType = IResponseErrors, typename DataType = std::monostate>
class Response {
private:
    std::unique_ptr<ErrorType> errors; // Use unique_ptr for better ownership semantics
    unsigned int status;
    DataType data;

public:
    /**
     * @brief Constructor for Response with errors.
     * @param errors The error object containing details of the response.
     */
    explicit Response(std::unique_ptr<ErrorType> errors, DataType data = {})
        : errors(std::move(errors)),
        status(this->errors ? this->errors->statusCode() : GENERAL_SUCCESS_RESPONSE_STATUS),
        data(std::move(data)) {
    }

    /**
     * @brief Constructor for Response with status and data only.
     * @param status The status code of the response.
     * @param data The response payload.
     */
    explicit Response(unsigned int status, DataType data = {})
        : errors(nullptr),
        status(status),
        data(std::move(data)) {
    }

    // Delete default constructor to enforce proper initialization.
    Response() = delete;

    static constexpr const char* DataKey = "Data";

    /**
     * @brief Gets the response code for this response.
     * @return The response code as specified by the template parameter.
     */
    ResponseCodes getCode() const {
        return Code;
    }

    /**
     * @brief Gets the data payload of the response.
     * @return The payload data.
     */
    const DataType& getData() const {
        return data;
    }

    /**
     * @brief Converts the response to a JSON object.
     * @return A JSON representation of the response.
     */
    virtual nlohmann::json getJson() const {
        nlohmann::json errorsJson = errors ? errors->getJson() : nlohmann::json();

        // Serialize data if possible
        nlohmann::json dataJson;
        if constexpr (!std::is_same_v<DataType, std::monostate>) {
            dataJson = data; 
        }

        nlohmann::json j = {
            {"Status", status},
            {DataKey, dataJson},
        };

        if (errors) {
            j["Errors"] = errorsJson;
        }

        return j;
    }

};

// Include specific error headers
#include "LoginResponseErrors.hpp"
#include "SignupResponseErrors.hpp"
#include "ResetPasswordResponseErrors.hpp"
#include "GeneralResponseErrors.hpp"

#include "RoomData.hpp"
#include "PlayerResults.hpp"
#include "GameStatus.hpp"
#include "PersonalStatistics.hpp"
#include "HighScoreInfo.hpp"
#include "RoomPreview.hpp"
#include "RoomState.hpp"
#include "GetQuestionResponseData.hpp"
#include <string>


// Macro for responses with data and a custom JSON key
#define DEFINE_RESPONSE_WITH_DATA(ResponseName, Code, ErrorType, DataType, KeyName) \
    template<> \
    constexpr const char* Response<Code, ErrorType, DataType>::DataKey = KeyName; \
    using ResponseName = Response<Code, ErrorType, DataType>;

// Responses without data
using StartGameResponse = Response<ResponseCodes::C_StartGameResponse, GeneralResponseErrors>;
using LeaveRoomResponse = Response<ResponseCodes::C_LeaveRoomResponse, IResponseErrors>;
using LeaveGameResponse = Response<ResponseCodes::C_LeaveGameResponse, GeneralResponseErrors>;
using LogoutResponse = Response<ResponseCodes::C_LogoutResponse, IResponseErrors>;
using LoginResponse = Response<ResponseCodes::C_LoginResponse, LoginResponseErrors>;
using SignupResponse = Response<ResponseCodes::C_SignupResponse, SignupResponseErrors>;
using PasswordCodeResponse = Response<ResponseCodes::C_SendPasswordResetCodeResponse, GeneralResponseErrors>;
using ResetPasswordResponse = Response<ResponseCodes::C_ResetPasswordResponse, ResetPasswordResponseErrors>;
using JoinRoomResponse = Response<ResponseCodes::C_JoinRoomResponse, GeneralResponseErrors>;
using Leave1v1WaitingListResponse = Response<ResponseCodes::C_Leave1v1WaitingListResponse, GeneralResponseErrors>;

// Responses with data and custom JSON key
DEFINE_RESPONSE_WITH_DATA(DidFound1v1MatchResponse, ResponseCodes::C_DidFound1v1MatchResponse, GeneralResponseErrors, bool, "FoundMatch");
DEFINE_RESPONSE_WITH_DATA(CreateRoomResponse, ResponseCodes::C_CreateRoomResponse, GeneralResponseErrors, RoomData, "RoomData");
DEFINE_RESPONSE_WITH_DATA(GetGameResultsResponse, ResponseCodes::C_GetGameResultsResponse, IResponseErrors, std::vector<PlayerResults>, "Results");
DEFINE_RESPONSE_WITH_DATA(GetGameStateResponse, ResponseCodes::C_GetGameStateResponse, IResponseErrors, GameStatus, "GameStatus");
DEFINE_RESPONSE_WITH_DATA(GetHighScoreResponse, ResponseCodes::C_GetHighScoreResponse, IResponseErrors, std::vector<HighScoreInfo>, "Statistics");
DEFINE_RESPONSE_WITH_DATA(GetPersonalStatisticsResponse, ResponseCodes::C_GetPersonalStatsResponse, IResponseErrors, PersonalStatistics, "Statistics");
DEFINE_RESPONSE_WITH_DATA(GetPlayersInRoomResponse, ResponseCodes::C_GetPlayersInRoomResponse, IResponseErrors, std::vector<LoggedUser>, "Players");
DEFINE_RESPONSE_WITH_DATA(GetRoomsResponse, ResponseCodes::C_GetRoomsResponse, IResponseErrors, std::vector<RoomPreview>, "Rooms");
DEFINE_RESPONSE_WITH_DATA(GetRoomStateResponse, ResponseCodes::C_GetRoomStateResponse, IResponseErrors, RoomState, "RoomState");
DEFINE_RESPONSE_WITH_DATA(ServerErrorResponse, ResponseCodes::C_ErrorResponse, IResponseErrors, std::string, "Message");
DEFINE_RESPONSE_WITH_DATA(SubmitAnswerResponse, ResponseCodes::C_SubmitAnswerResponse, GeneralResponseErrors, unsigned int, "CorrectAnswerId");
DEFINE_RESPONSE_WITH_DATA(VerifyPasswordResetCodeResponse, ResponseCodes::C_VerifyPasswordResetCodeResponse, GeneralResponseErrors, std::string, "PasswordResetTocken");

using GetQuestionResponse = Response<ResponseCodes::C_GetQuestionResponse, GeneralResponseErrors, GetQuestionResponseData>;


