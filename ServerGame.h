#pragma once
#include "ServerNetwork.h"
#include "NetworkData.h"
#include <iostream>
#include "MemFile.h"

using namespace std;
//   Tabel lezende berichten
extern void stuurbericht();
extern __int8 watuitvoeren;
extern __int8 watuitvoerenr;
extern void loopontvang();
extern void stopproces(const char *filename);
extern void startthread();
extern memFileCls* fileData;


class ServerGame
{

public:

    ServerGame(void);
    ~ServerGame(void);

    void update(char* network_data, unsigned int data_length, unsigned __int8 mpNo, unsigned __int8& adrs);

	void receiveFromClients();

	void sendActionPackets();
	ServerNetwork* network;
	

private:

   // IDs for the clients connecting for table in ServerNetwork 
    static unsigned int client_id;
	void temppr(char* ls);
   // The ServerNetwork object 
 

	// data buffer


 };

