#pragma once
#include <stdint.h>
#ifdef _WIN32
#include <ws2tcpip.h>
#pragma comment (lib, "Ws2_32.lib")
#endif

#include "NetworkServices.h"

#include <map>
#include <atomic>
#include "Custom/custom_string.h"
using namespace std; 



extern int vrijadres[100];
extern bool adresvervangen;
extern unsigned int toevoegenid;
extern bool zendallen;
extern unsigned int zendid;
extern unsigned int gavervadr;
extern bool recwebbool;

class ServerNetwork
{
public:
    ServerNetwork(void);
    ~ServerNetwork(void);

	// send data to all clients


	// receive incoming data
    
	
	// accept new connections
    void acceptNewClient();

    // Socket to listen for new connections
    SOCKET ListenSocket;

    // Socket to give to the clients
    SOCKET ClientSocket;

    // for error checking return values

	    // table to keep track of each client's socket
		
	
};

