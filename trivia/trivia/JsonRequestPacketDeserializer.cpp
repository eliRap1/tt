#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<unsigned char> buffer)
{
	// Extract the JSON part (skip 1 byte for code and 4 bytes for size)
	std::string jsonStr(buffer.begin() + 5, buffer.end());

	// Parse the JSON
	json j = json::parse(jsonStr);

	// Fill the struct
	LoginRequest request;
	request.username = j["username"];
	request.password = j["password"];
	return request;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<unsigned char> buffer)
{
	std::string jsonStr(buffer.begin() + 5, buffer.end());

	// Parse the JSON
	json j = json::parse(jsonStr);

	// Fill the struct
	SignupRequest request;
	request.username = j["username"];
	request.password = j["password"];
	request.email = j["email"];
	return request;
}