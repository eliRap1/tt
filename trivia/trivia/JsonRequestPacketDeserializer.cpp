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

GetPlayerInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayerInRoomRequest(std::vector<unsigned char> buffer)
{
	std::string jsonStr(buffer.begin(), buffer.end());
	json j = json::parse(jsonStr);

	GetPlayerInRoomRequest request;
	request.roomId = j["roomId"];
	return request;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(std::vector<unsigned char> buffer)
{
	std::string jsonStr(buffer.begin(), buffer.end());
	json j = json::parse(jsonStr);

	JoinRoomRequest request;
	request.roomId = j["roomId"];
	return request;
}
CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(std::vector<unsigned char> buffer)
{
	std::string jsonStr(buffer.begin(), buffer.end());
	json j = json::parse(jsonStr);

	CreateRoomRequest request;
	request.roomName = j["roomName"];
	request.answerTimeout = j["answerTimeout"];
	request.maxUsers = j["maxUsers"];
	request.QuestionsCount = j["QuestionsCount"];
	return request;
}