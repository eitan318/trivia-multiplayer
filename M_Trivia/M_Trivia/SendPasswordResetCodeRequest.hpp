#pragma once
#include <string>
#include "json.hpp"

template <typename T>
class JsonRequestPacketDeserializer;


/**
 * @class SendPasswordResetCodeRequest
 * @brief Represents a request to send the password-reset code to an email.
 */
class SendPasswordResetCodeRequest {
    friend class JsonRequestPacketDeserializer<SendPasswordResetCodeRequest>;
private:
    std::string email;
    SendPasswordResetCodeRequest(const nlohmann::json& j) :
        email(j.at("Email")) {

    }

public:

    const std::string& getEmail() const { return email; }

};
