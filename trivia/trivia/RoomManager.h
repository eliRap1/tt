#pragma once
#include "Room.h"
class RoomManager
{
private:
	std::map<unsigned int, Room> m_rooms;
public:
	void createRoom(LoggedUser user, RoomData roomData);
	void deleteRoom(int roomId);
	Room& getRoom(int roomId);
	unsigned int getRoomState(int roomId);
	std::vector<RoomData> getRooms();
};

