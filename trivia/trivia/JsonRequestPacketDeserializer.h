#pragma once
#include <string>
#include "json.hpp"
#include <iostream>
using json = nlohmann::json;
typedef struct LoginRequest
{
	std::string username;
	std::string password;
} LoginRequest;

typedef struct SignupRequest
{
	std::string username;
	std::string password;
	std::string email;
} SignupRequest;

class JsonRequestPacketDeserializer
{
public:
	
	static LoginRequest deserializeLoginRequest(std::vector<unsigned char> buffer);
	static SignupRequest deserializeSignupRequest(std::vector<unsigned char> buffer);
};

