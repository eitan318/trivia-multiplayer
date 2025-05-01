#include "SocketService.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

using std::string;


int SocketService::getIntFromSocket(SOCKET sc, int bytesNum)
{
	std::vector<char> buffer(bytesNum);
	int res = recv(sc, buffer.data(), bytesNum, 0);
	if (res == SOCKET_ERROR || res == 0)
	{
		throw std::exception("Error while receiving int from socket");
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
	int res = recv(sc, buffer.data(), bytesNum, 0);
	if (res == SOCKET_ERROR || res == 0)
	{
		throw std::exception("Error while receiving from socket");
	}
	return std::string(buffer.begin(), buffer.begin() + res);
}


char* SocketService::getPartFromSocket(SOCKET sc, int bytesNum)
{
	return getPartFromSocket(sc, bytesNum, 0);
}

char* SocketService::getPartFromSocket(SOCKET sc, int bytesNum, int flags)
{
	if (bytesNum == 0)
	{
		return (char*)"";
	}

	char* data = new char[bytesNum + 1];
	int res = recv(sc, data, bytesNum, flags);
	int err = WSAGetLastError();

	if (res == INVALID_SOCKET || res == 0)
	{
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(sc);
		throw std::exception(s.c_str());
	}

	data[bytesNum] = 0;
	return data;
}

void SocketService::sendData(SOCKET sc, const std::vector<char>& data)
{
	if (send(sc, data.data(), data.size(), 0) == SOCKET_ERROR)
	{
		throw std::exception("Error while sending message to client");
	}
}

void SocketService::sendData(SOCKET sc, const std::string& message)
{
	const char* data = message.c_str();

	if (send(sc, data, message.size(), 0) == SOCKET_ERROR)
	{
		throw std::exception("Error while sending message to client");
	}
}
