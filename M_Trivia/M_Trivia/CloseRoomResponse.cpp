#include "CloseRoomResponse.hpp"
#include "json.hpp"


CloseRoomResponse::CloseRoomResponse(unsigned int status)
	: Response(status)
{
}

ResponseCodes CloseRoomResponse::getCode() const
{
	return ResponseCodes::C_CloseRoomResponse;
}




