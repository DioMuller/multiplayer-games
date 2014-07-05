#pragma comment(lib, "ws2_32.lib")

#include <iostream> 
#include <WinSock2.h>
#include "JankenpoStructs.h"

#define MESSAGE_SIZE 512
#define PLAYER_COUNT 4

RPSValue values[PLAYER_COUNT];

void runThread(int id);


int main(int argc, char* argv[])
{
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

		// Process Clients.
		// Reply Clients.
	}

	// Finalize WSA.
	WSACleanup();
}