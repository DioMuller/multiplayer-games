#pragma comment(lib, "ws2_32.lib") 
#include <WinSock2.h> 
#include <iostream> 
#include <time.h>
using namespace std;

int main(int argc, char *argv[])
{
	char* server;
	WSADATA wsaData;

	if (argc > 1)
	{
		server = argv[1];
	}
	else
	{
		server = "127.0.0.1";
	}

	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (ret != 0)
	{
		std::cout << "Error registering socket: " << WSAGetLastError() << std::endl;
	}

	SOCKET mainSocket;
	mainSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (mainSocket == INVALID_SOCKET)
	{
		std::cout << "Error creating socket: " << WSAGetLastError() << std::endl;
	}
	else
	{
		sockaddr_in serverAddress;
		serverAddress.sin_family = AF_INET;
		serverAddress.sin_addr.s_addr = inet_addr(server);
		serverAddress.sin_port = htons(12345);

		ret = connect(mainSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress));

		if (ret == SOCKET_ERROR)
		{
			std::cout << "Error connecting to socket: " << WSAGetLastError() << std::endl;
		}

		char buffer[1];
		srand(time(0));
		buffer[0] = 'a' + (rand() % 26);

		// Send Data
		int result = send(mainSocket, buffer, 1, NULL);
		std::cout << "Character sent: " << buffer[0] << endl;

		// Receive Data
		if (recv(mainSocket, buffer, 1, 0))
		{
			std::cout << "Character received: " << buffer[0] << endl;
		}

		closesocket(mainSocket);
	}

	WSACleanup();

	system("pause");

	return 0;
}