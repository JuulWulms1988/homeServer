#pragma once

#ifdef _WIN32
#include <winsock2.h>
#include <Windows.h>

#define _SOCK_CLOSE_F(SVAR) closesocket(SVAR)
#define _SOCK_ENUM_COMP(SVAR, COMP) SVAR == COMP
#define _SOCK_RESULT_COMP(SVAR) SVAR <= 0
#endif

#ifndef _WIN32
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
typedef int SOCKET;

#define _SOCK_CLOSE_F(SVAR) close(SVAR)
#define _SOCK_ENUM_COMP(SVAR, COMP) SVAR < 0
#define _SOCK_RESULT_COMP(SVAR) SVAR < 0
#endif

namespace NetworkMethods {
	inline void sockCloseF(SOCKET x) { _SOCK_CLOSE_F(x); }
}
