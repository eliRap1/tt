#include "JsonResponsePacketSerializer.h"
/*
This function serializes the login response into a vector of unsigned char
input: the response to serialize
output: the serialized response
*/
std::vector<unsigned char> JsonResponsePacketSerializer::serializeLoginResponse(LoginResponse& response)
{
    json j;
    j["status"] = response.status;
    std::string jsonString = j.dump();
    std::vector<unsigned char> buffer;
    buffer.push_back(LOGIN_CODE);
	// each line of the next 4 is moving the size so only 1 byte will be taken each time 
    unsigned int size = jsonString.size();
    buffer.push_back((size >> 24) & 0xFF);
    buffer.push_back((size >> 16) & 0xFF);
    buffer.push_back((size >> 8) & 0xFF);
    buffer.push_back(size & 0xFF);
    // Append the JSON string itself
    buffer.insert(buffer.end(), jsonString.begin(), jsonString.end());
    return buffer;
}
/*
    this function serializes the error response into a vector of unsigned char
	input: the response to serialize
	output: the serialized response
*/
std::vector<unsigned char> JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse& response)
{
    json j;
    j["message"] = response.message;
    std::string jsonStr = j.dump();
    std::vector<unsigned char> buffer;
    buffer.push_back(ERROR_CODE);
    unsigned int len = jsonStr.size();
    buffer.push_back((len >> 24) & 0xFF);
    buffer.push_back((len >> 16) & 0xFF);
    buffer.push_back((len >> 8) & 0xFF);
    buffer.push_back(len & 0xFF);
    buffer.insert(buffer.end(), jsonStr.begin(), jsonStr.end());
    return buffer;
}
/*
    this function serializes the signup response into a vector of unsigned char
	input: the response to serialize
	output: the serialized response
*/
std::vector<unsigned char> JsonResponsePacketSerializer::serializeSignupResponse(SignupResponse& response)
{
    json j;
    j["status"] = response.status;
    std::string jsonStr = j.dump();
    std::vector<unsigned char> buffer;
    buffer.push_back(SIGNUP_CODE);
    unsigned int len = jsonStr.size();
    buffer.push_back((len >> 24) & 0xFF);
    buffer.push_back((len >> 16) & 0xFF);
    buffer.push_back((len >> 8) & 0xFF);
    buffer.push_back(len & 0xFF);
    buffer.insert(buffer.end(), jsonStr.begin(), jsonStr.end());
    return buffer;
}
