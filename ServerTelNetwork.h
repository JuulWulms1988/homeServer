#pragma once

#ifdef _WIN32
#include <ws2tcpip.h>
#pragma comment (lib, "Ws2_32.lib")
#endif

#include "NetworkServices.h"

#include <map>
#include "Custom/custom_string.h"
#include "NetworkData.h"
using namespace std; 




class ServerTelNetwork
{
public:
    ServerTelNetwork(void);
    ~ServerTelNetwork(void);

	// receive incoming data
    
	
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

