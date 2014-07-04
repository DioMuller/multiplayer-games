#pragma comment(lib, "ws2_32.lib")

#include <iostream> 
#include <WinSock2.h>

int main(int argc, char* argv[])
{
	WSADATA wsaData;

	// Initialize WSA.
	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (ret != 0)
	{
		std::cout << "Error registering socket: " << WSAGetLastError() << std::endl;
	}

	// Initialize Socket
	SOCKET mainSocket;
	mainSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (mainSocket == INVALID_SOCKET)
	{
		std::cout << "Error creating socket: " << WSAGetLastError() << std::endl;
	}
	else
	{
		// Initialize listener port.
		// Wait for clients.
		// Process Clients.
		// Reply Clients.
	}

	// Finalize WSA.
	WSACleanup();
	return 0;
}