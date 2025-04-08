#pragma once
#include <curl/curl.h>
#include <string>
#include <iostream>

class ApiClient {
public:
	static std::string generateTriviaQuestionsUrl(int amount, int category, const std::string& type);
	static std::string getQuestionsJson(const char*);
};
