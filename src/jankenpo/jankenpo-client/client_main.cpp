#pragma comment(lib, "ws2_32.lib")

#include <iostream> 
#include <string>
#include <WinSock2.h>
#include "JankenpoStructs.h"

int main(int argc, char* argv[])
{
	// Server and port info
	const char* server;
	int port;
	// WSA Data
	WSADATA wsaData;

	system("cls");

	// Tries to connect to given server. If no server is given, connect to localhost.
	if (argc > 1) server = argv[1];
	else server = "10.97.241.21"; //"127.0.0.1";

	// Tries to connect to given port. If no port is given, connect to default port.
	if (argc > 2) port = std::stoi(argv[2]);
	else port = 12345;

	std::cout << "Connecting to server " << server << ":" << port << std::endl;

	// Initializes WSA.
	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (ret != 0)
	{
		std::cout << "Error registering socket: " << WSAGetLastError() << std::endl;
		system("pause");
		return -1;
	}

	// Initialize Socket.
	SOCKET mainSocket;
	mainSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (mainSocket == INVALID_SOCKET)
	{
		std::cout << "Error creating socket: " << WSAGetLastError() << std::endl;
		system("pause");
		return -1;
	}
	else
	{
		// Create Data.
		MessageRPSConnect* game;
		game = new MessageRPSConnect();

		// Connect to the server.
		sockaddr_in serverAddress;
		serverAddress.sin_family = AF_INET;
		serverAddress.sin_addr.s_addr = inet_addr(server);
		serverAddress.sin_port = htons(port);

		ret = connect(mainSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress));

		if (ret == SOCKET_ERROR)
		{
			std::cout << "Error connecting to socket: " << WSAGetLastError() << std::endl;
			system("pause");
			return -1;
		}

		// Send Data.
		send(mainSocket, (const char*)game, sizeof(MessageRPSRequest), 0);
				
		// Wait Response.
		MessageRPSRequest* req;
		do
		{
			std::cout << "Waiting for the game request..." << std::endl;
			char buffer[MESSAGE_SIZE];
			ret = recv(mainSocket, buffer, MESSAGE_SIZE, 0);
			req = (MessageRPSRequest*)buffer;
			if (!req) std::cout << "Received an invalid package." << std::endl;
			else if (req->type != MessageType::MESSAGE_RPS_REQUEST) std::cout << "Received package with an invalid type." << std::endl;
		} while (!req || req->type != MessageType::MESSAGE_RPS_REQUEST);

		// Print Response.
		std::cout << "New game requested!" << std::endl;

		// Get Data.
		int value = 0;

		while (value <= 0 || value > 3)
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
				// Send to server.
				MessageRPSPlay* play = new MessageRPSPlay();
				play->value = (RPSValue) value;
				send(mainSocket, (const char*)play, sizeof(MessageRPSPlay), 0);

				// Wait Response.
				MessageRPSResult* result;
				do
				{
					std::cout << "Waiting for the game result..." << std::endl;
					char buffer[MESSAGE_SIZE];
					ret = recv(mainSocket, buffer, MESSAGE_SIZE, 0);
					result = (MessageRPSResult*)buffer;

					if (!result) std::cout << "Received an invalid package." << std::endl;
					else if (result->type != MessageType::MESSAGE_RPS_RESULT) std::cout << "Received package with an invalid type." << std::endl;
				} while (!result || result->type != MessageType::MESSAGE_RPS_RESULT);

				switch (result->winner)
				{
					case DuelResult::WIN:
						std::cout << "I won!" << std::endl;
						break;
					case DuelResult::LOSE:
						std::cout << "I lost!" << std::endl;
						break;
					case DuelResult::DRAW:
						std::cout << "Draw!" << std::endl;
						break;
					default:
						std::cout << "What the Fuck?!" << std::endl;
						break;
				}
			}
		}

	}

	// Finalize WSA.
	closesocket(mainSocket);
	WSACleanup();

	// Pause so the program will not close after finishing.
	system("pause");

	return 0;
}