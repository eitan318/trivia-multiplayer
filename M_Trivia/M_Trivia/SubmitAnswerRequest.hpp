#pragma once
#include "UserRecord.hpp"
#include "json.hpp"

template <typename T> class JsonRequestPacketDeserializer;

/**
 * @class SubmitAnswerRequest
 * @brief Represents a submitted answer of user.
 */
class SubmitAnswerRequest {
	friend class JsonRequestPacketDeserializer<SubmitAnswerRequest>;

private:
	unsigned int correctAnswerId;

	SubmitAnswerRequest(const nlohmann::json& j);

public:
	const unsigned int getAnswerId() const;
};
