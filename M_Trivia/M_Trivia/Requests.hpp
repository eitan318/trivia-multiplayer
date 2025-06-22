#pragma once

#include "RoomData.hpp"
#include "UserRecord.hpp"
#include "json.hpp"
#include <string>

#define DEFINE_REQUEST_STRUCT(RequestName, FieldType, FieldName, JsonFieldName) \
struct RequestName {                                                            \
    FieldType FieldName;                                                        \
                                                                                 \
    /* Constructor from JSON */                                                 \
    explicit RequestName(const nlohmann::json& j) {                             \
        j.at(JsonFieldName).get_to(FieldName);                                  \
    }                                                                           \
};
\

// Define request structures or aliases for different request types
DEFINE_REQUEST_STRUCT(CreateRoomRequest, RoomData, roomData, "RoomData");
DEFINE_REQUEST_STRUCT(GetHighScoreRequest, unsigned int, topPlayersAmount, "TopPlayersLimit");
DEFINE_REQUEST_STRUCT(GetPlayersInRoomRequest, unsigned int, roomId, "RoomId");
DEFINE_REQUEST_STRUCT(JoinRoomRequest, unsigned int, roomId, "RoomId");
DEFINE_REQUEST_STRUCT(SendPasswordResetCodeRequest, std::string, email, "Email");
DEFINE_REQUEST_STRUCT(SignupRequest, UserRecord, userRecord, "UserRecord");
DEFINE_REQUEST_STRUCT(SubmitAnswerRequest, unsigned int, answerId, "ChosenAnswerId");
DEFINE_REQUEST_STRUCT(VerifyPasswordResetCodeRequest, std::string, resetCode, "PasswordResetCode");



struct LoginRequest {
    std::string username;
    std::string password;

    explicit LoginRequest(const nlohmann::json& j) {
        j.at("Username").get_to(username);
        j.at("Password").get_to(password);
    }

};

struct ResetPasswordRequest {
    std::string email;
    std::string newPassword;
    std::string resetPasswordTocken;

    explicit ResetPasswordRequest(const nlohmann::json& j) {
        j.at("Email").get_to(email);
        j.at("NewPassword").get_to(newPassword);
        j.at("ResetPasswordTocken").get_to(resetPasswordTocken);
    }
};