// JsonResponsePacketSerializer.cpp
#include "JsonResponsePacketSerializer.h"

using json = nlohmann::json;

enum ResponseCode {
    LOGIN_CODE = 1,
    SIGNUP_CODE = 2,
    ERROR_CODE = 3,
    LOGOUT_CODE = 4,
    GET_ROOMS_CODE = 5,
    GET_PLAYERS_IN_ROOM_CODE = 6,
    JOIN_ROOM_CODE = 7,
    CREATE_ROOM_CODE = 8,
    HIGH_SCORE_CODE = 9,
    PERSONAL_STATS_CODE = 10
};

std::vector<unsigned char> JsonResponsePacketSerializer::serializeLoginResponse(const LoginResponse& res) {
    json j;
    j["status"] = res.status;
    std::string dump = j.dump();
    std::vector<unsigned char> buffer;
    buffer.push_back(LOGIN_CODE);
    int len = dump.size();
    buffer.push_back((len >> 24) & 0xFF);
    buffer.push_back((len >> 16) & 0xFF);
    buffer.push_back((len >> 8) & 0xFF);
    buffer.push_back(len & 0xFF);
    buffer.insert(buffer.end(), dump.begin(), dump.end());
    return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeSignupResponse(const SignupResponse& res) {
    json j;
    j["status"] = res.status;
    std::string dump = j.dump();
    std::vector<unsigned char> buffer;
    buffer.push_back(SIGNUP_CODE);
    int len = dump.size();
    buffer.push_back((len >> 24) & 0xFF);
    buffer.push_back((len >> 16) & 0xFF);
    buffer.push_back((len >> 8) & 0xFF);
    buffer.push_back(len & 0xFF);
    buffer.insert(buffer.end(), dump.begin(), dump.end());
    return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeErrorResponse(const ErrorResponse& res) {
    json j;
    j["message"] = res.message;
    std::string dump = j.dump();
    std::vector<unsigned char> buffer;
    buffer.push_back(ERROR_CODE);
    int len = dump.size();
    buffer.push_back((len >> 24) & 0xFF);
    buffer.push_back((len >> 16) & 0xFF);
    buffer.push_back((len >> 8) & 0xFF);
    buffer.push_back(len & 0xFF);
    buffer.insert(buffer.end(), dump.begin(), dump.end());
    return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeLogoutResponse(const LogoutResponse& res) {
    json j;
    j["status"] = res.status;
    std::string dump = j.dump();
    std::vector<unsigned char> buffer;
    buffer.push_back(LOGOUT_CODE);
    int len = dump.size();
    buffer.push_back((len >> 24) & 0xFF);
    buffer.push_back((len >> 16) & 0xFF);
    buffer.push_back((len >> 8) & 0xFF);
    buffer.push_back(len & 0xFF);
    buffer.insert(buffer.end(), dump.begin(), dump.end());
    return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeGetRoomResponse(const GetRoomResponse& res) {
    json j;
    j["status"] = res.status;
    j["rooms"] = json::array();
    for (const auto& room : res.rooms) {
        json r;
        r["id"] = room.id;
        r["name"] = room.name;
        r["maxPlayers"] = room.maxPlayers;
        r["questionCount"] = room.numOfQuestionsInGame;
        r["timePerQuestion"] = room.timePerQuestion;
        r["isActive"] = room.isActive;
        j["rooms"].push_back(r);
    }
    std::string dump = j.dump();
    std::vector<unsigned char> buffer;
    buffer.push_back(GET_ROOMS_CODE);
    int len = dump.size();
    buffer.push_back((len >> 24) & 0xFF);
    buffer.push_back((len >> 16) & 0xFF);
    buffer.push_back((len >> 8) & 0xFF);
    buffer.push_back(len & 0xFF);
    buffer.insert(buffer.end(), dump.begin(), dump.end());
    return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeGetPlayersInRoomResponse(const GetPlayersInRoomResponse& res) {
    json j;
    j["players"] = res.players;
    std::string dump = j.dump();
    std::vector<unsigned char> buffer;
    buffer.push_back(GET_PLAYERS_IN_ROOM_CODE);
    int len = dump.size();
    buffer.push_back((len >> 24) & 0xFF);
    buffer.push_back((len >> 16) & 0xFF);
    buffer.push_back((len >> 8) & 0xFF);
    buffer.push_back(len & 0xFF);
    buffer.insert(buffer.end(), dump.begin(), dump.end());
    return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeJoinRoomResponse(const JoinRoomResponse& res) {
    json j;
    j["status"] = res.status;
    std::string dump = j.dump();
    std::vector<unsigned char> buffer;
    buffer.push_back(JOIN_ROOM_CODE);
    int len = dump.size();
    buffer.push_back((len >> 24) & 0xFF);
    buffer.push_back((len >> 16) & 0xFF);
    buffer.push_back((len >> 8) & 0xFF);
    buffer.push_back(len & 0xFF);
    buffer.insert(buffer.end(), dump.begin(), dump.end());
    return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeCreateRoomResponse(const CreateRoomResponse& res) {
    json j;
    j["status"] = res.status;
    std::string dump = j.dump();
    std::vector<unsigned char> buffer;
    buffer.push_back(CREATE_ROOM_CODE);
    int len = dump.size();
    buffer.push_back((len >> 24) & 0xFF);
    buffer.push_back((len >> 16) & 0xFF);
    buffer.push_back((len >> 8) & 0xFF);
    buffer.push_back(len & 0xFF);
    buffer.insert(buffer.end(), dump.begin(), dump.end());
    return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeHighScoreResponse(const getHighScoresResponse& res) {
    json j;
    j["highScores"] = res.highScores;
    std::string dump = j.dump();
    std::vector<unsigned char> buffer;
    buffer.push_back(HIGH_SCORE_CODE);
    int len = dump.size();
    buffer.push_back((len >> 24) & 0xFF);
    buffer.push_back((len >> 16) & 0xFF);
    buffer.push_back((len >> 8) & 0xFF);
    buffer.push_back(len & 0xFF);
    buffer.insert(buffer.end(), dump.begin(), dump.end());
    return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializePersonalStatsResponse(const getPersonalStatsResponse& res) {
    json j;
    j["statistics"] = res.statistics;
    std::string dump = j.dump();
    std::vector<unsigned char> buffer;
    buffer.push_back(PERSONAL_STATS_CODE);
    int len = dump.size();
    buffer.push_back((len >> 24) & 0xFF);
    buffer.push_back((len >> 16) & 0xFF);
    buffer.push_back((len >> 8) & 0xFF);
    buffer.push_back(len & 0xFF);
    buffer.insert(buffer.end(), dump.begin(), dump.end());
    return buffer;
}
