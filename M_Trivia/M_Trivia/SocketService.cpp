#include "SocketService.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <stdexcept>

using std::string;

int SocketService::getIntFromSocket(SOCKET sc, int bytesNum)
{
    std::vector<char> buffer(bytesNum);
    int totalReceived = 0;

    while (totalReceived < bytesNum)
    {
        int res = recv(sc, buffer.data() + totalReceived, bytesNum - totalReceived, 0);
        if (res == SOCKET_ERROR || res == 0)
        {
            throw std::runtime_error("Error while receiving int from socket");
        }
        totalReceived += res;
    }

    int value = 0;
    for (int i = 0; i < bytesNum; ++i)
    {
        value = (value << 8) | (unsigned char)buffer[i];
    }
    return value;
}

std::string SocketService::getStringPartFromSocket(SOCKET sc, int bytesNum)
{
    std::vector<char> buffer(bytesNum);
    int totalReceived = 0;

    while (totalReceived < bytesNum)
    {
        int res = recv(sc, buffer.data() + totalReceived, bytesNum - totalReceived, 0);
        if (res == SOCKET_ERROR || res == 0)
        {
            throw std::runtime_error("Error while receiving from socket");
        }
        totalReceived += res;
    }

    return std::string(buffer.begin(), buffer.end());
}

void SocketService::sendData(SOCKET sc, const std::vector<char>& data)
{
    int totalSent = 0;
    while (totalSent < data.size())
    {
        int res = send(sc, data.data() + totalSent, data.size() - totalSent, 0);
        if (res == SOCKET_ERROR)
        {
            throw std::runtime_error("Error while sending message to client");
        }
        totalSent += res;
    }
}
