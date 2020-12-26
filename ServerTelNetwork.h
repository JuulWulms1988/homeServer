#pragma once
#include <winsock2.h>
#include <Windows.h>
#include "NetworkServices.h"
#include <ws2tcpip.h>
#include <map>
#include "NetworkData.h"
using namespace std; 
#pragma comment (lib, "Ws2_32.lib")



class ServerTelNetwork
{
public:
    ServerTelNetwork(void);
    ~ServerTelNetwork(void);

	// receive incoming data
    int receiveData(unsigned int client_id, char * recvbuf);
	
	// accept new connections
    SOCKET acceptNewClient();

    // Socket to listen for new connections
    SOCKET ListenSocket;

    // Socket to give to the clients
    SOCKET ClientSocket;

    // for error checking return values
    int iResult;

    // table to keep track of each client's socket

};

