#pragma once
#include "json.hpp"
#include <string>

template <typename T> class JsonRequestPacketDeserializer;

/**
 * @class LoginRequest
 * @brief Represents a request to log in.
 */
class VerifyPasswordResetCodeRequest {
	friend class JsonRequestPacketDeserializer<VerifyPasswordResetCodeRequest>;

private:
	std::string codeFromClient;

	VerifyPasswordResetCodeRequest(const nlohmann::json& j);

public:
	const std::string& getCodeFromClient() const;
};
