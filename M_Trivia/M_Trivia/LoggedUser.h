#pragma once
#include <string>
#include "json.hpp"


class LoggedUser {
public:

	std::string m_username;
	std::string getUsername() const{
		return this->m_username;
	}
};



/**
 * @brief Converts a HighScoreInfo object into a JSON object.
 *
 * This function serializes the provided `HighScoreInfo` struct into a JSON object.
 * @param j The JSON object to which the data will be written.
 * @param highScoreInfo The HighScoreInfo object that contains the data to be serialized.
 */
inline void to_json(nlohmann::json& j, const LoggedUser& user) {
	j = nlohmann::json{
		{"Username", user.getUsername()},
	};
}