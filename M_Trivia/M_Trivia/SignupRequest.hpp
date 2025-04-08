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

        // PASSWORD
        std::regex passwordRegex(R"(^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[!@#$%^&*]).{8,}$)");
        if (!std::regex_match(password, passwordRegex)) {
            throw std::runtime_error("Invalid password: must be 8+ chars, include upper/lower letters, digit, special char.");
        }

        // EMAIL
        std::regex emailRegex(R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.(com|co\.il|cyber\.org\.il)$)");
        if (!std::regex_match(email, emailRegex)) {
            throw std::runtime_error("Invalid email format.");
        }

        // ADDRESS (format: Street, Apt, City)
        std::smatch match;
        std::regex addressRegex(R"(^([A-Za-z\s]+),\s*(\d+),\s*([A-Za-z\s]+)$)");
        if (!std::regex_match(address, match, addressRegex)) {
            throw std::runtime_error("Invalid address format. Use: Street, Apt, City");
        }
        std::string street = match[1];
        std::string apt = match[2];
        std::string city = match[3];

        // PHONE
        std::regex phoneRegex(R"(^0(2|3|4|5\d)-\d{7}$)");
        if (!std::regex_match(phone, phoneRegex)) {
            throw std::runtime_error("Invalid phone number. Expected format: 0X-XXXXXXX");
        }

        // BIRTH DATE
        std::regex dateRegex(R"(^(0[1-9]|[12][0-9]|3[01])[-/.](0[1-9]|1[0-2])[-/.](19|20)\d{2}$)");
        if (!std::regex_match(birthDate, dateRegex)) {
            throw std::runtime_error("Invalid birth date format. Expected: DD.MM.YYYY or DD/MM/YYYY");
        }

        // All fields passed validation
        request.userRecord = UserRecord(username, password, email, address, phone, birthDate);
    }
};