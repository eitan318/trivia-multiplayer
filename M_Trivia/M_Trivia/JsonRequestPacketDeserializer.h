#include "json.hpp"
#include <vector>
#include <stdexcept>

/**
 * @class JsonRequestPacketDeserializer
 * @brief A utility class for deserializing JSON request packets into specific types.
 *
 * This class uses the `nlohmann::json` library to parse JSON data from a buffer and convert it into
 * an object of the specified type. It requires the type `T` to implement a `from_json` function
 * to support the deserialization process.
 *
 * @tparam T The type of the object to deserialize into.
 */
template <typename T>
class JsonRequestPacketDeserializer {
public:
    /**
     * @brief Deleted default constructor to prevent instantiation of the class.
     *
     * This class is meant to be used as a static utility and should not be instantiated.
     */
    JsonRequestPacketDeserializer() = delete;

    /**
     * @brief Deserializes a JSON request from a buffer into an object of type `T`.
     *
     * This method parses the given buffer into a JSON object and converts it into an
     * instance of type `T` using the `nlohmann::json` library. It expects the type `T`
     * to have a `from_json` method or a `get_to` specialization.
     *
     * @param buffer A vector of characters containing the JSON data.
     * @return An object of type `T` initialized with the deserialized data.
     * @throws std::runtime_error If parsing the JSON fails.
     */
    static T deserializeRequest(const std::vector<char>& buffer) {
        try {
            // Parse the buffer into a JSON object
            nlohmann::json j = nlohmann::json::parse(buffer);

            // Create an instance of T
            T request;

            // Manually call from_json to populate the request object
            from_json(j, request);

            return request;
        }
        catch (const nlohmann::json::exception& e) {
            // Throw a runtime error if JSON parsing or conversion fails
            throw std::runtime_error(std::string("Request parse error: ") + e.what());
        }
    }

};
