#pragma once
#include "RequestHandlerFactory.h"
typedef struct RoomData 
{
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	//RoomStatus status;
} RoomData;
class Room
{
private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
public:
	Room(const LoggedUser& user, const RoomData& metadata) : m_metadata(metadata) { m_users.push_back(user); }
	void addUser(const LoggedUser& user) { m_users.push_back(user); }
	void removeUser(const LoggedUser& user) { m_users.erase(std::remove(m_users.begin(), m_users.end(), user), m_users.end()); }
	const std::vector<std::string> getUsers() const { return std::vector<std::string>(m_users.begin(), m_users.end()); }
	const RoomData& getRoomData() const { return m_metadata; }
};

