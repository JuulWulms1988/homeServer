#ifdef _WIN32
#include "../stdafx.h"
#endif

#include "ServerTelNetwork.h"
#include <iostream>


ServerTelNetwork::ServerTelNetwork(void)
{
	#ifdef _WIN32
    // create WSADATA object
    WSADATA wsaData;

    // our sockets for the server
    ListenSocket = INVALID_SOCKET;
    ClientSocket = INVALID_SOCKET;



    // address info for the server to listen to
    struct addrinfo *result = NULL;
    struct addrinfo hints;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        exit(1);
    }

    // set address information
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;    // TCP connection!!!
    hints.ai_flags = AI_PASSIVE;

	    // Resolve the server address and port
    iResult = getaddrinfo(NULL, "10003", &hints, &result);

    if ( iResult != 0 ) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        exit(1);
    }

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        exit(1);
    }

    // Set the mode of the socket to be nonblocking
    u_long iMode = 0;
    iResult = ioctlsocket(ListenSocket, FIONBIO, &iMode);

    if (iResult == SOCKET_ERROR) {
        printf("ioctlsocket failed with error: %d\n", WSAGetLastError());
        _SOCK_CLOSE_F(ListenSocket);
        WSACleanup();
        exit(1);
    }

    // Setup the TCP listening socket
    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);

    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        _SOCK_CLOSE_F(ListenSocket);
        WSACleanup();
        exit(1);
    }

    // no longer need address information
    freeaddrinfo(result);

    // start listening for new clients attempting to connect
    iResult = listen(ListenSocket, SOMAXCONN);

    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        _SOCK_CLOSE_F(ListenSocket);
        WSACleanup();
        exit(1);
    }
    #endif

    #ifndef _WIN32
    struct sockaddr_in hints;
    memset(&hints, '\0', sizeof(struct sockaddr_in));
    ListenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (ListenSocket < 0) exit(1);
      int opt = 1;
    if (setsockopt(ListenSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
    &opt, sizeof(opt))) exit(1);
    hints.sin_family = AF_INET;
    hints.sin_addr.s_addr = INADDR_ANY;
    hints.sin_port = htons(10003);
    if (bind(ListenSocket, (struct sockaddr *) &hints, sizeof(hints)) < 0) 
        _SOCK_CLOSE_F(ListenSocket), exit(1);
    if (listen(ListenSocket,128) < 0)
        _SOCK_CLOSE_F(ListenSocket), exit(1);
    #endif
}


ServerTelNetwork::~ServerTelNetwork(void)
{
}

// accept new connections
SOCKET ServerTelNetwork::acceptNewClient()
{
	do {
		// if client waiting, accept the connection and save the socket
		ClientSocket = accept(ListenSocket, NULL, NULL);
		if (_SOCK_ENUM_COMP(ClientSocket, INVALID_SOCKET)) continue;
		
        #ifdef _WIN32
        char value = 1;
      
		setsockopt(ClientSocket, IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value));
       #endif
		return ClientSocket;
	} while (true);
}


// send data to all clients

