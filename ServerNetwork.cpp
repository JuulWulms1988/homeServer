#include "StdAfx.h"
#include "ServerNetwork.h"
#include <iostream>

extern unsigned __int8 adres[100];
extern void TH_FFVOOrtijd(SOCKET* ClientSocket);



ServerNetwork::ServerNetwork(void)
{
	// create WSADATA object
		WSADATA wsaData;
		// our sockets for the server
		ListenSocket = INVALID_SOCKET;
		ClientSocket = INVALID_SOCKET;



		// address info for the server to listen to
		struct addrinfo *result = NULL;
		struct addrinfo hints;

		// Initialize Winsock
		int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			exit(1);
		}

		// set address information
		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;    // TCP connection!!!
		hints.ai_flags = AI_PASSIVE;

		// Resolve the server address and port
		iResult = getaddrinfo(NULL, "10002", &hints, &result);

		if (iResult != 0) {
			WSACleanup();
			exit(1);
		}

		// Create a SOCKET for connecting to server
		ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

		if (ListenSocket == INVALID_SOCKET) {
			freeaddrinfo(result);
			WSACleanup();
			exit(1);
		}

		// Set the mode of the socket to be nonblocking
		//u_long iMode = 1;
		//iResult = ioctlsocket(ListenSocket, FIONBIO, &iMode);

		if (iResult == SOCKET_ERROR) {
			closesocket(ListenSocket);
			WSACleanup();
			exit(1);
		}

		// Setup the TCP listening socket
		iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);

		if (iResult == SOCKET_ERROR) {
			freeaddrinfo(result);
			closesocket(ListenSocket);
			WSACleanup();
			exit(1);
		}

		// no longer need address information
		freeaddrinfo(result);

		// start listening for new clients attempting to connect
		iResult = listen(ListenSocket, SOMAXCONN);

		if (iResult == SOCKET_ERROR) {
			closesocket(ListenSocket);
			WSACleanup();
			exit(1);
		}
}


ServerNetwork::~ServerNetwork(void)
{
}

// accept new connections
void ServerNetwork::acceptNewClient()
{
	while (true) {
		// if client waiting, accept the connection and save the socket
		ClientSocket = accept(ListenSocket, NULL, NULL);

		if (ClientSocket != INVALID_SOCKET)
		{
			//disable nagle on the client's socket
			char value = 1;

			setsockopt(ClientSocket, IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value));
			
			TH_FFVOOrtijd(&ClientSocket);
		}
	}
}


// send data to all clients
bool ServerNetwork::receive(SOCKET* s, char * packets, int& totalSize)
{
	if ((totalSize = NetworkServices::receiveMessage(*s, packets, totalSize)) == SOCKET_ERROR) { cout << "ERROROROR\n"; return false; } cout << "WELBERICHT!"; return true;
}

