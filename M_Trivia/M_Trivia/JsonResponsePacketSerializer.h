#pragma once
#include <vector>
#include "Response.hpp"
#include "json.hpp"


#define MSG_CODE_SIZE 1

class JsonResponsePacketSerializer
{
public:
    static std::vector<char> serializeResponse(const Response& response)
    {
        std::vector<char> res;
        res.push_back((char)response.getCode()); // Add the message code at the start

        // Convert the response to JSON
        std::string json_str = response.getJson().dump();

        // Get the size of the JSON string
        int json_length = json_str.size();
        res.resize(res.size() + sizeof(int)); // Allocate space for the length of the JSON string
        std::memcpy(res.data() + MSG_CODE_SIZE, &json_length, sizeof(int)); // Add the JSON length after the message code

        // Add the JSON string to the response
        res.insert(res.end(), json_str.begin(), json_str.end());

        return res;
    }

};

