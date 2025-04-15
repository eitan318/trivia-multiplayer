#include "json.hpp"
#include <vector>
#include <stdexcept>

template <typename T>
class JsonRequestPacketDeserializer {
public:
    JsonRequestPacketDeserializer() = delete;
    // Template method to deserialize the request
    static T deserializeRequest(const std::vector<char>& buffer) {
        try {
            nlohmann::json j = nlohmann::json::parse(buffer);
            T request;
            j.get_to(request);  // Calls from_json if it exists
            return request;
        }
        catch (const nlohmann::json::exception& e) {
            throw std::runtime_error(std::string("Request parse error: ") + e.what());
        }
    }
};
