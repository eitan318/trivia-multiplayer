#include "SignupResponse.hpp"
#include "json.hpp"


SignupResponse::SignupResponse(SignupResponseErrors* signupResponseErrors)
     : Response(signupResponseErrors){
}

ResponseCodes SignupResponse::getCode() const 
{
	return ResponseCodes::C_SignupResponse; 
}
