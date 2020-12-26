#pragma once
#include <winsock2.h>
#include <Windows.h>
#include "NetworkServices.h"
#include <ws2tcpip.h>
#include <map>
#include <atomic>
using namespace std; 
#pragma comment (lib, "Ws2_32.lib")


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
	bool receive(SOCKET* s, char * packets, int& totalSize);

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

