#pragma once
#include <winsock2.h>
#include <Windows.h>
#include "NetworkServices.h"
#include <ws2tcpip.h>
#include <map>
#include <string>
using namespace std; 
#pragma comment (lib, "Ws2_32.lib")




class ServerintNetwork
{
public:
    ServerintNetwork(void);
    ~ServerintNetwork(void);

	// send data to all clients
    void sendTo(const unsigned int* id, char * bericht, unsigned int* len);
	// receive incoming data
    int receiveData(const unsigned int * client_id, char * recvbuf);
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

