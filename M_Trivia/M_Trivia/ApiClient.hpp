#pragma once
#include <string>

/**
 * @class ApiClient
 * @brief Provides methods to interact with the Open Trivia Database (OpenTDB) API.
 *
 * This class offers functionality to generate URLs for trivia question requests and
 * to fetch JSON data from the API using cURL.
 */
class ApiClient {
public:
    /**
     * @brief Generates a URL for fetching trivia questions from the OpenTDB API.
     *
     * Constructs a URL based on the specified parameters for amount, category, and question type.
     *
     * @param amount The number of questions to request.
     * @param category The category ID of the questions.
     * @param type The type of questions (e.g., "multiple" for multiple choice).
     * @return The constructed URL as a string.
     */
    static std::string generateTriviaQuestionsUrl(int amount, int category, const std::string& type);

    /**
     * @brief Fetches trivia questions in JSON format from the specified URL.
     *
     * Uses cURL to perform an HTTP GET request to the provided URL and returns the response as a string.
     *
     * @param url The URL to fetch the JSON data from.
     * @return The JSON response as a string.
     * @throws std::runtime_error If cURL initialization fails.
     */
    static std::string getQuestionsJson(const char* url);
};
