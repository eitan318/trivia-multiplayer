#include "ApiClient.h"

#include <curl/curl.h>
#include <iostream>


size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
	size_t totalSize = size * nmemb;
	userp->append((char*)contents, totalSize);
	return totalSize;
}

std::string ApiClient::generateTriviaQuestionsUrl(int amount, int category, const std::string& type)
{
    std::string url = "https://opentdb.com/api.php?";
    url += "amount=" + std::to_string(amount);
    url += "&category=" + std::to_string(category);
    url += "&type=" + type;
    return url;
}


std::string ApiClient::getQuestionsJson(const char* url) {
	CURL* curl;
	CURLcode res;
	std::string readBuffer;

	curl = curl_easy_init(); // Initialize cURL
	if (!curl) {
		throw std::runtime_error("Failed to initialize cURL");
	}
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

	res = curl_easy_perform(curl); // Perform the request
	if (res != CURLE_OK) {
		std::cerr << "cURL Error: " << curl_easy_strerror(res) << std::endl;
	}

	curl_easy_cleanup(curl); // Cleanup
	return readBuffer;
}