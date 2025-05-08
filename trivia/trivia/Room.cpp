#include "Room.h"

Room::Room(const LoggedUser& user, const RoomData& metadata) : m_metadata(metadata) { m_users.push_back(user); }
void Room::addUser(const LoggedUser& user) { m_users.push_back(user); }
void Room::removeUser(const LoggedUser& user)
{
	m_users.erase(std::remove(m_users.begin(), m_users.end(), user), m_users.end());
}

const std::vector<std::string> Room::getUsers() const {
	std::vector<std::string> usernames;
	for (const auto& user : m_users) {
		usernames.push_back(user.getUsername());
	}
	return usernames;
}

const RoomData& Room::getRoomData() const { return m_metadata; }