#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(const LoggedUser& user, RequestHandlerFactory& factory)
    : m_loggedUser(user), m_handlerFactory(factory) {}

bool RoomAdminRequestHandler::isRequestRelevant(const RequestInfo& request)
{
    return request.id == CLOSE_ROOM_CODE || request.id == START_GAME_CODE || request.id == GET_ROOM_STATE_CODE;
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo& request)
{
    switch (request.id)
    {
    case CLOSE_ROOM_CODE:
        return closeRoom(request);
    case START_GAME_CODE:
        return startGame(request);
    case GET_ROOM_STATE_CODE:
        return getRoomState(request);
    default:
        ErrorResponse err{ "Invalid request for RoomAdmin" };
        return { JsonResponsePacketSerializer::serializeResponse(err), this };
    }
}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo& request)
{
    int roomId = -1;
    for (const auto& room : m_handlerFactory.getRoomManager().getRooms())
    {
        auto& r = m_handlerFactory.getRoomManager().getRoom(room.id);
        auto users = r.getUsers();
        if (std::find(users.begin(), users.end(), m_loggedUser.getUsername()) != users.end())
        {
            roomId = room.id;
            break;
        }
    }

    if (roomId == -1)
    {
        ErrorResponse err{ "Room not found for user" };
        return { JsonResponsePacketSerializer::serializeResponse(err), this };
    }

    auto users = m_handlerFactory.getRoomManager().getRoom(roomId).getUsers();
    LeaveRoomResponse response{ 1 };
    auto buffer = JsonResponsePacketSerializer::serializeResponse(response);

    for (const auto& username : users)
    {
        std::cout << "[Admin] Sending LeaveRoomResponse to: " << username << std::endl;
    }

    m_handlerFactory.getRoomManager().deleteRoom(roomId);

    return { buffer, m_handlerFactory.createMenuRequestHandler(m_loggedUser) };
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo& request)
{
    int roomId = -1;
    for (const auto& room : m_handlerFactory.getRoomManager().getRooms())
    {
        auto& r = m_handlerFactory.getRoomManager().getRoom(room.id);
        auto users = r.getUsers();
        if (std::find(users.begin(), users.end(), m_loggedUser.getUsername()) != users.end())
        {
            roomId = room.id;
            break;
        }
    }

    if (roomId == -1)
    {
        ErrorResponse err{ "Room not found for user" };
        return { JsonResponsePacketSerializer::serializeResponse(err), this };
    }

    StartGameResponse response{ 1 };
    auto buffer = JsonResponsePacketSerializer::serializeResponse(response);

    auto users = m_handlerFactory.getRoomManager().getRoom(roomId).getUsers();
    for (const auto& username : users)
    {
        std::cout << "[Admin] Sending StartGameResponse to: " << username << std::endl;
    }

    return { buffer, nullptr };
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo& request)
{
    int roomId = -1;
    for (const auto& room : m_handlerFactory.getRoomManager().getRooms())
    {
        auto& r = m_handlerFactory.getRoomManager().getRoom(room.id);
        auto users = r.getUsers();
        if (std::find(users.begin(), users.end(), m_loggedUser.getUsername()) != users.end())
        {
            roomId = room.id;
            break;
        }
    }

    if (roomId == -1)
    {
        ErrorResponse err{ "Room not found for user" };
        return { JsonResponsePacketSerializer::serializeResponse(err), this };
    }

    RoomData data = m_handlerFactory.getRoomManager().getRoom(roomId).getRoomData();
    auto users = m_handlerFactory.getRoomManager().getRoom(roomId).getUsers();

    GetRoomStateResponse response{
        1,
        false, // returns false because start game does not exist!!!! (eli dont scream at me)
        users,
        data.numOfQuestionsInGame,
        data.timePerQuestion
    };

    return { JsonResponsePacketSerializer::serializeResponse(response), this };
}
