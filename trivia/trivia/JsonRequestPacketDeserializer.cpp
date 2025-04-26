#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<unsigned char> buffer)
{
	std::string jsonStr(buffer.begin(), buffer.end()); 

	json j = json::parse(jsonStr);

	LoginRequest request;
	request.username = j["username"];
	request.password = j["password"];
	return request;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<unsigned char> buffer)
{
	std::string jsonStr(buffer.begin(), buffer.end());

	json j = json::parse(jsonStr);

	SignupRequest request;
	request.username = j["username"];
	request.password = j["password"];
	request.email = j["email"];
	return request;
}