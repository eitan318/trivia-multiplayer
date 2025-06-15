#pragma once
#include <string>
#include "json.hpp"


class LoggedUser {
private:
	std::string m_username;
public:
	LoggedUser(const std::string& username);
	std::string getUsername() const;

	bool operator<(const LoggedUser& other) const;
	bool operator==(const LoggedUser& other) const;

};

/**
 * @brief Converts a LoggedUser object into a JSON object.
 *
 * This function serializes the provided `LoggedUser` struct into a JSON object.
 * @param j The JSON object to which the data will be written.
 * @param user The LoggedUser object that contains the data to be serialized.
 */
inline void to_json(nlohmann::json& j, const LoggedUser& user) {
	j = nlohmann::json{
		{"Username", user.getUsername()},
	};
}