#include "RequestInfo.hpp"

RequestInfo::RequestInfo(unsigned char code, const time_t& recivalTime,
    const std::vector<char>& buffer)
    : code(code), receivalTime(recivalTime), buffer(buffer) {}
