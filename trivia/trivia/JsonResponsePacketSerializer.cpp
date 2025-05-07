// JsonResponsePacketSerializer.cpp
#include "JsonResponsePacketSerializer.h"

using json = nlohmann::json;
/*
    made this help function to make it easier to add length
*/
static void addLengthToBuffer(std::vector<unsigned char>& buffer, int len) 
{
    buffer.push_back((len >> 24) & 0xFF);
    buffer.push_back((len >> 16) & 0xFF);
    buffer.push_back((len >> 8) & 0xFF);
    buffer.push_back(len & 0xFF);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const ErrorResponse& res) {
    json j;
    j["message"] = res.message;
    std::string dump = j.dump();
    std::vector<unsigned char> buffer;
    buffer.push_back(ERROR_CODE);
    addLengthToBuffer(buffer, dump.size());
    buffer.insert(buffer.end(), dump.begin(), dump.end());
    return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const LoginResponse& res) {
    json j;
    j["status"] = res.status;
    std::string dump = j.dump();
    std::vector<unsigned char> buffer;
    buffer.push_back(LOGIN_CODE);
    addLengthToBuffer(buffer, dump.size());
    buffer.insert(buffer.end(), dump.begin(), dump.end());
    return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const SignupResponse& res) {
    json j;
    j["status"] = res.status;
    std::string dump = j.dump();
    std::vector<unsigned char> buffer;
    buffer.push_back(SIGNUP_CODE);
    addLengthToBuffer(buffer, dump.size());
    buffer.insert(buffer.end(), dump.begin(), dump.end());
    return buffer;
}

