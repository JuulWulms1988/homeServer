#pragma once

#ifdef _WIN32
#include <ws2tcpip.h>
#pragma comment (lib, "Ws2_32.lib")
#endif
#include "NetworkServices.h"
#include <map>
#include "Custom/custom_string.h"

using namespace std; 

class ServerintNetwork
{
public:
    ServerintNetwork(void);
    ~ServerintNetwork(void);

	// send data to all clients
   
	// receive incoming data
    
	void leegmap(const unsigned int *id);
	void maakmap(const unsigned int *id);
	// accept new connections
    void acceptNewClient();
	void accF();

    // Socket to listen for new connections
    SOCKET ListenSocket;

    // Socket to give to the clients
    SOCKET ClientSocket;

    // for error checking return values
    int iResult;

	    // table to keep track of each client's socket
	map<unsigned int, SOCKET> sessions;
	map<unsigned int, bool> blank;
	map<unsigned int, char*> req;
	map<unsigned int, unsigned int> reqlen;
};

