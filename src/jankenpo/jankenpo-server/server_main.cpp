#pragma comment(lib, "ws2_32.lib")

#include <iostream> 
#include <WinSock2.h>
#include <thread>
#include "JankenpoStructs.h"

#define PLAYER_COUNT 2

RPSValue values[PLAYER_COUNT];

void runThread(int id);


int main(int argc, char* argv[])
{
	while (true)
	{
		std::thread th1(runThread, 0);
		std::thread th2(runThread, 1);

		th1.join();
		th2.join();
	}

	return 0;
}

void runThread(int id)
{
	WSADATA wsaData;

	// Initialize WSA.
	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (ret != 0)
	{
		std::cout << "Error registering socket: " << WSAGetLastError() << std::endl;
		return;
	}

	// Initialize Socket
	SOCKET mainSocket;
	mainSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (mainSocket == INVALID_SOCKET)
	{
		std::cout << "Error creating socket: " << WSAGetLastError() << std::endl;
		return;
	}
	else
	{
		// Initialize listener port.
		sockaddr_in address;
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = inet_addr("0.0.0.0");
		address.sin_port = htons(12340 + id);
		// Wait for clients.
		ret = bind(mainSocket, (SOCKADDR*)&address, sizeof(address));
		if (ret != 0)
		{
			std::cout << "Error binding socket: " << WSAGetLastError() << std::endl;
			return;
		}

		ret = listen(mainSocket, SOMAXCONN);
		if (ret != 0)
		{
			std::cout << "Error listening socket: " << WSAGetLastError() << std::endl;
			return;
		}

		// Process Client.
		SOCKET clientSocket;
		sockaddr_in clientAddress;
		int clientAddressSize = sizeof(sockaddr_in);
		clientSocket = accept(mainSocket, (SOCKADDR*)&clientAddress, &clientAddressSize);

		char buffer[MESSAGE_SIZE];
		MessageRPSConnect *conn = nullptr;
		do
		{
			std::cout << "Waiting for clients..." << std::endl;
			char buffer[MESSAGE_SIZE];
			ret = recv(mainSocket, buffer, MESSAGE_SIZE, 0);
			conn = (MessageRPSConnect*)buffer;
			if (!conn) std::cout << "Received an invalid package." << std::endl;
			else if (conn->type != MessageType::MESSAGE_RPS_CONNECT) std::cout << "Received package with an invalid type." << std::endl;
		} while (!conn || conn->type != MessageType::MESSAGE_RPS_CONNECT);

		// Reply Clients.
	}

	// Finalize WSA.
	WSACleanup();
}