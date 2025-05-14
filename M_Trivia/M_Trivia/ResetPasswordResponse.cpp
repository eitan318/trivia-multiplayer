#include "ResetPasswordResponse.hpp"
#include "json.hpp"




ResetPasswordResponse::ResetPasswordResponse(ResetPasswordResponseErrors* resetPasswordResponseErrors)
	: Response(resetPasswordResponseErrors	) {
}


ResponseCodes ResetPasswordResponse::getCode() const 
{
	return ResponseCodes::C_ResetPasswordResponse;
}

