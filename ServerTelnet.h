#pragma once
#include "ServerTelNetwork.h"
#include "NetworkData.h"

class ServerTelnet
{

public:
	ServerTelNetwork* network;
	ServerTelnet(void) { network = new ServerTelNetwork(); };
    void update();

	bool receiveFromClients(SOCKET S);



private:

   // IDs for the clients connecting for table in ServerNetwork 


   // The ServerNetwork object 


	// data buffer
 
   void accept_piScreen(unsigned int clNo, SOCKET clSock);
};