#pragma once
#include <algorithm>
#include "RoomData.h"
#include "LoggedUser.h"
#include <vector>


class Room
{
public:
	Room(const LoggedUser& user, const RoomData& metadata);
	void addUser(const LoggedUser& user);
	void removeUser(const LoggedUser& user);
	const std::vector<std::string> getUsers() const;
	const RoomData& getRoomData() const;
private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
};

