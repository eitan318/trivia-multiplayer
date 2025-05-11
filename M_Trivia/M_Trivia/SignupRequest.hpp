#pragma once
#include "UserRecord.hpp"
#include "json.hpp"

template <typename T>
class JsonRequestPacketDeserializer;


/**
 * @class SignupRequest
 * @brief Represents a request to signup a user.
 */
class SignupRequest {
    friend class JsonRequestPacketDeserializer<SignupRequest>;
private:
    UserRecord userRecord;

    SignupRequest(const nlohmann::json& j) {
        const std::string username = j.at("Username");
        const std::string password = j.at("Password");
        const std::string email = j.at("Email");
        const std::string address = j.at("HouseAddress");
        const std::string phone = j.at("PhoneNumber");
        const std::string birthDate = j.at("BirthDate");

        this->userRecord = UserRecord(username, password, email, address, phone, birthDate);
    }
public:


    const UserRecord& getUserRecord() const { return userRecord; }
};
