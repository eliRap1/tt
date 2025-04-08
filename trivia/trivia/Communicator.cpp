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
	ULONG ip = INADDR_ANY;
	sa.sin_addr.s_addr = ip;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// Connects between the socket and the configuration (port and etc..)
	if (bind(this->m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(this->m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << PORT << std::endl;
	while (true)
	{
		SOCKET clientSocket = accept(this->m_serverSocket, NULL, NULL);
		if (clientSocket == INVALID_SOCKET)
		{
			//std::cout << "Accept failed" << std::endl;
		}
		else
		{
			IRequestHandler* newClient = new LoginRequestHandler();
			this->m_clients[clientSocket] = newClient;
			std::thread th(&Communicator::handleNewClients, this, clientSocket);
			th.detach();
			std::cout << "Client connected" << std::endl;
		}
	}
}

void Communicator::handleNewClients(SOCKET clientSocket)
{
	bool isExit = false;
	std::string input = "Hello";
	char buffer[1024];
	send(clientSocket, input.c_str(), input.size(), 0);
	while (!isExit)
	{
		int bytesReceived = recv(clientSocket, buffer, 1024, 0);
		if (bytesReceived == 0)
		{
			isExit = true;
		}
		else if (bytesReceived < 0)
		{
			// handle error
		}
		else
		{
			buffer[bytesReceived] = '\0';
			std::cout << buffer << std::endl;
		}
		if(input == "exit")
		{
			isExit = true;
		}
		//input = this->m_clients[clientSocket]->handleRequest(input);
	}
	closesocket(clientSocket);
	delete this->m_clients[clientSocket];
	this->m_clients.erase(clientSocket);
	std::cout << "Client disconnected" << std::endl;

}

void Communicator::startHandleRequests()
{
	bindAndListen();
}