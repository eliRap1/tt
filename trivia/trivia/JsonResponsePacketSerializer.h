#pragma once
#include <iostream>
#include <vector>
#include "json.hpp"
#define LOGIN_CODE "e"
#define SIGNUP_CODE "f"
#define ERROR_CODE 999
using json = nlohmann::json;
typedef struct LoginResponse 
{
	unsigned int status;
} LoginResponse;
typedef struct ErrorResponse
{
	std::string message;
} ErrorResponse;
typedef struct SignupResponse 
{
	unsigned int status;
} SignupResponse;
class JsonResponsePacketSerializer
{
public:
	static std::vector<unsigned char> serializeLoginResponse(LoginResponse& response);
	static std::vector<unsigned char> serializeErrorResponse(ErrorResponse& response);
	static std::vector<unsigned char> serializeSignupResponse(SignupResponse& response);

};

