#pragma once
#include "../Custom/custom_network.h"
#ifdef _WIN32
#include <Ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")
#endif
#include <iostream>

class udpBasCls {
public:
	udpBasCls() {
		#ifdef _WIN32
		WSADATA wsaData;
		WSAStartup(MAKEWORD(2, 2), &wsaData);
		#endif
		serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	}

protected:
	SOCKET serverSocket;

	static void setAddr(sockaddr_in& sIn, u_short port, char* ip) {
		sIn.sin_family = AF_INET;
		#ifdef _WIN32
		inet_pton(AF_INET, ip, &sIn.sin_addr.s_addr);
		#endif
		#ifndef _WIN32
		sIn.sin_addr.s_addr = inet_addr(ip);
		#endif
		sIn.sin_port = htons(port);
	}

	void send(char* buf, int len, sockaddr_in& x) {
		sendto(serverSocket, buf, len, 0, (sockaddr*)&x, (int)sizeof(x));
	}
};