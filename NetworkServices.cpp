#ifdef _WIN32
#include "../stdafx.h"
#endif

#include "NetworkServices.h"
#include "Custom/custom_string.h"
using namespace std;

int NetworkServices::sendMessage(SOCKET curSocket, char * message, int messageSize)
{
	
	return send(curSocket, message, messageSize, 0);
}

int NetworkServices::receiveMessage(SOCKET curSocket, char * buffer, int bufSize)
{
    return recv(curSocket, buffer, bufSize, 0);
}

