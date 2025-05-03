#pragma once
#include <vector>
#include "Response.hpp"
#include "json.hpp"

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
     * @brief Serializes a `Response` object into a vector of characters.
     *
     * The serialization format is as follows:
     * - The first byte contains the message code (`getCode()`).
     * - The next 4 bytes contain the length of the serialized JSON string.
     * - The remaining bytes contain the JSON string representation of the response data.
     *
     * @param response The `Response` object to serialize.
     * @return A vector of characters containing the serialized response.
     */
    static std::vector<char> serializeResponse(const Response& response)
    {
        std::vector<char> res;

        // Add the message code as the first byte
        res.push_back((char)response.getCode());

        // Convert the response data to a JSON string
        std::string json_str = response.getJson().dump();

        // Get the length of the JSON string
        int json_length = json_str.size();

        // Allocate space for the length of the JSON string (4 bytes)
        res.resize(res.size() + sizeof(int));

        // Copy the JSON length into the vector after the message code
        std::memcpy(res.data() + MSG_CODE_SIZE, &json_length, sizeof(int));

        // Append the JSON string to the vector
        res.insert(res.end(), json_str.begin(), json_str.end());

        return res;
    }
};
