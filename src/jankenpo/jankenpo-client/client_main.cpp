#pragma comment(lib, "ws2_32.lib")

#include <iostream> 
#include <string>
#include <WinSock2.h>

int main(int argc, char* argv[])
{
	// Server and port info
	const char* server;
	int port;
	// WSA Data
	WSADATA wsaData;

	// Tries to connect to given server. If no server is given, connect to localhost.
	if (argc > 1) server = argv[1];
	else server = "127.0.0.1";

	// Tries to connect to given port. If no port is given, connect to default port.
	if (argc > 2) port = std::stoi(argv[2]);
	else port = 12345;

	// Initializes WSA.
	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (ret != 0)
	{
		std::cout << "Error registering socket: " << WSAGetLastError() << std::endl;
	}

	// Initialize Socket.
	SOCKET mainSocket;
	mainSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (mainSocket == INVALID_SOCKET)
	{
		std::cout << "Error creating socket: " << WSAGetLastError() << std::endl;
	}
	else
	{
		// Connect to the server.
		sockaddr_in serverAddress;
		serverAddress.sin_family = AF_INET;
		serverAddress.sin_addr.s_addr = inet_addr(server);
		serverAddress.sin_port = htons(port);

		ret = connect(mainSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress));

		if (ret == SOCKET_ERROR)
		{
			std::cout << "Error connecting to socket: " << WSAGetLastError() << std::endl;
		}

		// Get Data.
		int value = 0;

		while ( value <= 0 || value > 3)
		{
			std::cout << "Select your weapon!" << std::endl;
			std::cout << "1 - Rock" << std::endl;
			std::cout << "2 - Paper" << std::endl;
			std::cout << "3 - Scissors" << std::endl;
			std::cin >> value;

			if (value <= 0 || value > 3)
			{
				std::cout << "Invalid input." << std::endl;
				system("pause");
			}
			else
			{ 
				// Send Data.

				// Wait Response.

				// Print Response.
			}
		}

	}

	// Finalize WSA.
	WSACleanup();

	// Pause so the program will not close after finishing.
	system("pause");

	return 0;
}