#pragma once
#include <regex>
#include "UserRecord.hpp"
#include "json.hpp"

struct SignupRequest {
	UserRecord userRecord;


	friend void from_json(const nlohmann::json& j, SignupRequest& request) {
        const std::string username = j.at("username");
        const std::string password = j.at("password");
        const std::string email = j.at("email");
        const std::string address = j.at("house_address");
        const std::string phone = j.at("phone_number");
        const std::string birthDate = j.at("birth_date");

        

        // All fields passed validation
        request.userRecord = UserRecord(username, password, email, address, phone, birthDate);
    }
};