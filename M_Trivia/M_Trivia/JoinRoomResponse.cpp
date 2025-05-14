#include "JoinRoomResponse.hpp"
#include "json.hpp"


JoinRoomResponse::JoinRoomResponse(JoinRoomResponseErrors* errors) 
	: Response(errors)
{
}
	
ResponseCodes JoinRoomResponse::getCode() const 
{
	return ResponseCodes::C_JoinRoomResponse; 
}




