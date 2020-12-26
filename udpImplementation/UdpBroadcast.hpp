#pragma once
#include <WinSock2.h>
#include <Ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")
#include <IOStream>

class udpBasCls {
public:
	udpBasCls() {
		WSADATA wsaData;
		WSAStartup(MAKEWORD(2, 2), &wsaData);
		serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	}

protected:
	SOCKET serverSocket = INVALID_SOCKET;

	static void setAddr(sockaddr_in& sIn, u_short port, char* ip) {
		sIn.sin_family = AF_INET;
		inet_pton(AF_INET, ip, &sIn.sin_addr.s_addr);
		sIn.sin_port = htons(port);
	}

	void send(char* buf, int len, sockaddr_in& x) {
		sendto(serverSocket, buf, len, 0, (SOCKADDR*)&x, (int)sizeof(x));
	}
};