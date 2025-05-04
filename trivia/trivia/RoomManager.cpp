#include "RoomManager.h"

void RoomManager::createRoom(LoggedUser user, RoomData roomData)
{
	Room room(user,roomData);
	this->m_rooms[roomData.id] = room;
}

void RoomManager::deleteRoom(int roomId)
{
	this->m_rooms.erase(roomId);
}
Room& RoomManager::getRoom(int roomId)
{
	return this->m_rooms[roomId];
}
unsigned int RoomManager::getRoomState(int roomId)
{

}
std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> roomsData;
	for (auto room : this->m_rooms)
		roomsData.push_back(room.second.getRoomData());
	return roomsData;
}