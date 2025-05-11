#pragma once
#include <WinSock2.h>
#include <vector>
#include <string>


class SocketService
{
public:
	/**
	 * @brief Reads an integer from a socket.
	 * @param sc The socket to read from.
	 * @param bytesNum The number of bytes to read.
	 * @return The integer value read from the socket.
	 * @throws std::exception if there is an error while reading from the socket.
	 */
	static int getIntFromSocket(SOCKET sc, int bytesNum);
	
	/**
	 * @brief Reads a string from a socket.
	 * @param sc The socket to read from.
	 * @param bytesNum The number of bytes to read.
	 * @return The string read from the socket.
	 * @throws std::exception if there is an error while reading from the socket.
	 */
	static std::string getStringPartFromSocket(SOCKET sc, int bytesNum);
	
	/**
	 * @brief Sends binary data through a socket.
	 * @param sc The socket to send data to.
	 * @param data A vector containing the data to send.
	 * @throws std::exception if there is an error while sending data.
	 */
	static void sendData(SOCKET sc, const std::vector<char>& data);
	
	/**
	 * @brief Sends a string through a socket.
	 * @param sc The socket to send data to.
	 * @param message The string message to send.
	 * @throws std::exception if there is an error while sending data.
	 */
	static void sendData(SOCKET sc, const std::string& message);

};


#ifdef _DEBUG // vs add this define in debug mode
#include <stdio.h>
// Q: why do we need traces ?
// A: traces are a nice and easy way to detect bugs without even debugging
// or to understand what happened in case we miss the bug in the first time
#define TRACE(msg, ...) printf(msg "\n", __VA_ARGS__);
// for convenient reasons we did the traces in stdout
// at general we would do this in the error stream like that
// #define TRACE(msg, ...) fprintf(stderr, msg "\n", __VA_ARGS__);

#else // we want nothing to be printed in release version
#define TRACE(msg, ...) printf(msg "\n", __VA_ARGS__);
#define TRACE(msg, ...) // do nothing
#endif