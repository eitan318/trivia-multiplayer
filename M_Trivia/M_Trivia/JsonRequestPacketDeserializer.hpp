#include <concepts>
#include "json.hpp"
#include <vector>
#include <stdexcept>

//// Concept to check if a type supports deserialization via nlohmann::json
//template <typename T>
//concept Deserializable = requires(const nlohmann::json & j, T obj) {
//    { j.get<T>() }; // Ensure the type is compatible with `j.get<T>()`
//};

class JsonRequestPacketDeserializer {
public:
    JsonRequestPacketDeserializer() = delete;

    template <typename T>
    static T deserializeRequest(const std::vector<char>& buffer) {
        try {
            nlohmann::json j = nlohmann::json::parse(buffer);
            return T{ j };  // Use the constructor T(const nlohmann::json&)
        }
        catch (const nlohmann::json::exception& e) {
            throw std::runtime_error(std::string("Request parse error: ") + e.what());
        }
    }
};

