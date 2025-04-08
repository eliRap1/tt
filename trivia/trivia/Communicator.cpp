#include "Communicator.h"


void Communicator::bindAndListen()
{
	WSAInitializer wsaInit;
	this->m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->m_serverSocket == INVALID_SOCKET)
	{
		throw std::runtime_error("socket failed");
	}


	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(PORT); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// Connects between the socket and the configuration (port and etc..)
	if (bind(this->m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(this->m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << PORT << std::endl;
}

void Communicator::handleNewClients(SOCKET clientSocket)
{
	if (clientSocket == INVALID_SOCKET)
	{
		throw std::runtime_error("accept failed");
	}
	IRequestHandler* newClient = new LoginRequestHandler();
	this->m_clients[clientSocket] = newClient;
}

void Communicator::startHandleRequests()
{
	bindAndListen();
	while(true)
	{
		SOCKET clientSocket = accept(this->m_serverSocket, NULL, NULL);
		if (clientSocket == INVALID_SOCKET)
		{
			continue;
		}
		std::thread th(&Communicator::handleNewClients, this, clientSocket);
		th.detach();
		std::cout << "Client connected" << std::endl;
	}
}