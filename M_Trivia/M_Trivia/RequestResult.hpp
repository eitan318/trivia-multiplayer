#pragma once
#include <vector>
#include <string>
#include "IRequestHandler.h"

struct IRequestHandler;

struct RequestResult {
    std::vector<char> response;
    IRequestHandler* newHandler = nullptr; 
};
