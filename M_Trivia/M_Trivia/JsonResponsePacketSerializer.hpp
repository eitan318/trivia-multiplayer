#pragma once
#include <vector>
#include "Response.hpp"

#define MSG_CODE_SIZE 1

/**
 * @class JsonResponsePacketSerializer
 * @brief A utility class for serializing responses into a binary format.
 *
 * This class converts a `Response` object into a vector of characters that can be transmitted
 * over a network or stored. The serialized format consists of:
 * - A single byte for the message code.
 * - An integer (4 bytes) representing the size of the JSON string.
 * - The JSON string containing the response data.
 */
class JsonResponsePacketSerializer
{
public:
    /**
     * @brief Deleted default constructor to prevent instantiation of the class.
     *
     * This class is intended to be used as a static utility and should not be instantiated.
     */
    JsonResponsePacketSerializer() = delete;

    /**
     * @brief Serializes a templated `Response` object into a vector of characters.
     *
     * The serialization format is as follows:
     * - The first byte contains the message code (`getCode()`).
     * - The next 4 bytes contain the length of the serialized JSON string.
     * - The remaining bytes contain the JSON string representation of the response data.
     *
     * @tparam Code The response code type, corresponding to `ResponseCodes`.
     * @tparam ErrorType The type of errors, defaulting to `IResponseErrors`.
     * @param response The templated `Response` object to serialize.
     * @return A vector of characters containing the serialized response.
     */
    template<ResponseCodes Code, typename ErrorType = IResponseErrors, typename DataType = std::monostate>
    static std::vector<char> serializeResponse(const Response<Code, ErrorType, DataType>& response) {
        std::vector<char> res;

        // Add the message code as the first byte
        res.push_back(static_cast<char>(Code));

        // Convert the response data to a JSON string
        std::string json_str = response.getJson().dump();

        // Get the length of the JSON string
        uint32_t json_length = static_cast<uint32_t>(json_str.size());

        // Append the length of the JSON string in little-endian format
        for (size_t i = 0; i < sizeof(uint32_t); ++i) {
            res.push_back(static_cast<char>((json_length >> (i * 8)) & 0xFF));
        }

        // Append the JSON string to the vector
        res.insert(res.end(), json_str.begin(), json_str.end());

        return res;
    }

};
