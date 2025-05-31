#include "CloseRoomResponse.hpp"
#include "json.hpp"


CloseRoomResponse::CloseRoomResponse(CloseRoomResponseErrors* errors)
	: Response(errors)
{
}

ResponseCodes CloseRoomResponse::getCode() const
{
	return ResponseCodes::C_CloseRoomResponse;
}




