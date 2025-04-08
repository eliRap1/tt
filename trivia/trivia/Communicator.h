#pragma comment (lib, "ws2_32.lib")
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <map>
#include <thread>
#include "WSAInitializer.h"

#include "LoginRequestHandler.h"
#define PORT 3353
#define SERVER "127.0.0.1"

class Communicator
{
private:
	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;

	void bindAndListen();
	void handleNewClients(SOCKET c);

public:
	void startHandleRequests();
};
