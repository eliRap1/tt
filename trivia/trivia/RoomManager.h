#pragma once
#include "Room.h"
#include "LoggedUser.h"
#include <map>
#include <vector>

class RoomManager
{
public:
	void createRoom(LoggedUser user, RoomData roomData);
	void deleteRoom(int roomId);
	Room& getRoom(int roomId);
	unsigned int getRoomState(int roomId);
	std::vector<RoomData> getRooms();
private:
	std::map<unsigned int, Room> m_rooms;
};

