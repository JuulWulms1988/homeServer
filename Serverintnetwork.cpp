#include "StdAfx.h"
#include "ServerintNetwork.h"
#include <iostream>


ServerintNetwork::ServerintNetwork(void)
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
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
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
    iResult = getaddrinfo(NULL, "10004", &hints, &result);

    if ( iResult != 0 ) {
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
   // u_long iMode = 0;
   // iResult = ioctlsocket(ListenSocket, FIONBIO, &iMode);

    if (iResult == SOCKET_ERROR) {
        closesocket(ListenSocket);
        WSACleanup();
        exit(1);
    }

    // Setup the TCP listening socket
    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);

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


ServerintNetwork::~ServerintNetwork(void)
{
}

// accept new connections
void ServerintNetwork::acceptNewClient()
{
	while (true) {
		// if client waiting, accept the connection and save the socket
		ClientSocket = accept(ListenSocket, NULL, NULL);
		if (ClientSocket == INVALID_SOCKET) continue;

		//disable nagle on the client's socket
		char value = 1;
		setsockopt(ClientSocket, IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value));
		// insert new client into session id tab
		accF();
	}
}

void ServerintNetwork::leegmap(const unsigned int* id) {
	std::map<unsigned int, unsigned int>::iterator itt = reqlen.find(*id);
	if (itt != reqlen.end() && itt->second > 0) {
		std::map<unsigned int, char*>::iterator it = req.find(*id);
		delete[itt->second + 1] it->second;
	}
	if (blank.find(*id) != blank.end()) {
		blank.erase(blank.find(*id));
	}
	if (req.find(*id) != req.end()) {
		req.erase(req.find(*id));
	}
	if (reqlen.find(*id) != reqlen.end()) {
		reqlen.erase(reqlen.find(*id));
	}
	if (sessions.find(*id) != sessions.end()) {
		sessions.erase(sessions.find(*id));
	}
}
void ServerintNetwork::maakmap(const unsigned int* id){
	sessions.insert(pair<unsigned int, SOCKET>(*id, ClientSocket));
	blank.insert(pair<unsigned int, bool>(*id, 0));
	req.insert(pair<unsigned int, char*>(*id, new char));
	std::map<unsigned int, char*>::iterator it = req.find(*id); delete it->second;
	reqlen.insert(pair<unsigned int, unsigned int>(*id, 0));
}

int ServerintNetwork::receiveData(const unsigned int * client_id, char * recvbuf)
{
	if (sessions.find(*client_id) != sessions.end())
		{
		SOCKET currentSocket = sessions[*client_id];
		for (int tel = 0; tel < 20; tel++) {
			iResult = NetworkServices::receiveMessage(currentSocket, recvbuf, 10000);
			if (iResult > 0) {
		//		for (int tol = 0; tol < iResult; tol++) {
		//			cout << recvbuf[tol];
		//		}
		//		cout << "\n\nDeze lengte: " << iResult << "\n\n";
			}
			if (iResult == 0)
		{
			if (tel == 19) {
				leegmap(client_id);
				closesocket(currentSocket);
			}
		}
		else {
			break;
		}
	}
        return iResult;
	}
    return 0;
}

void ServerintNetwork::sendTo(const unsigned int* id, char * bericht, unsigned int* len) {
	std::map<unsigned int, SOCKET>::iterator iter;
	int iSendResult;
	iter = sessions.find(*id);
	if (iter != sessions.end()) {
		//for (unsigned int tel = 0; tel < *len; tel++) {
		//	cout << *(bericht + tel);
		//}
	//	cout << "\nLengte: " << *len << "\n\n";
		for (int tel = 0; tel < 20; tel++) {
			iSendResult = NetworkServices::sendMessage(iter->second, bericht, *len);
			if (iSendResult == SOCKET_ERROR)
			{
				if (tel == 19) {
				closesocket(iter->second);
				//leegmap(&iter->second);
				}
			}
			else {
				break;
			}
		}
	}
}