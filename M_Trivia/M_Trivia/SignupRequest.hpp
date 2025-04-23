#pragma once
#include <regex>
#include "UserRecord.hpp"
#include "json.hpp"

/**
 * @class SendPasswordResetCodeRequest
 * @brief Represents a request to signup a user.
 */
struct SignupRequest {
    // The user data as it will be in a db record
	UserRecord userRecord;


    /**
  * @brief Deserializes a JSON object into a SignupRequest object.
  *
  * @param j The JSON object to deserialize.
  * @param request The SignupRequest object to populate.
  */
	friend void from_json(const nlohmann::json& j, SignupRequest& request) {
        const std::string username = j.at("Username");
        const std::string password = j.at("Password");
        const std::string email = j.at("Email");
        const std::string address = j.at("HouseAddress");
        const std::string phone = j.at("PhoneNumber");
        const std::string birthDate = j.at("BirthDate");

        

        // All fields passed validation
        request.userRecord = UserRecord(username, password, email, address, phone, birthDate);
    }
};