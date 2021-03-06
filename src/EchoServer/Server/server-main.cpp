#pragma comment(lib, "ws2_32.lib") 
#include <WinSock2.h> 
#include <iostream> 
using namespace std;

int main(int argc, char *argv[])
{
	WSADATA wsaData;
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
		serverAddress.sin_addr.s_addr = inet_addr("0.0.0.0");
		serverAddress.sin_port = htons(12345);

		ret = bind(mainSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress));

		// Waiting Client
		while (1)
		{

			ret = listen(mainSocket, SOMAXCONN);

			std::cout << "Awaiting clients..." << std::endl;
			SOCKET clientReceivedSocket;
			sockaddr_in clientAddress;
			int clientAddressSize = sizeof(sockaddr_in);

			clientReceivedSocket = accept(mainSocket, (SOCKADDR*)&clientAddress, &clientAddressSize);

			// Print address on the prompt.
			std::cout << "Client Connected: " << inet_ntoa(clientAddress.sin_addr) << endl;

			// Receive Data
			char buffer[1];
			if (recv(clientReceivedSocket, buffer, 1, 0))
			{
				std::cout << "Character received: " << buffer[0] << endl;
				buffer[0] = toupper(buffer[0]);

				// Send Character back
				int result = send(clientReceivedSocket, buffer, 1, NULL);
				std::cout << "Character sent: " << buffer[0] << endl;
			}
		}

		closesocket(mainSocket);
		
	}

	WSACleanup();

	return 0;
}