#pragma once

#include "ServerTelnet.h"
#include "ThreadCls.h"

struct telnetStr;

extern telnetStr& telnetS;
struct telnetStr {
	void rmAdArF(SOCKET S);
	ServerTelnet serv;
	mutex tMut;
	mutex mut;
	bool fl;
	condition_variable cv;
	void chkAdVoeg(SOCKET S);
	ServerTelnet& deLock(SOCKET S) {
		mut.lock(), fl = true, mut.unlock(), cv.notify_all(), chkAdVoeg(S); return serv;
	}
	void lisAccept(SOCKET s) {
		fl = false;
		threadBufCls::recStruct{ tMut, [](void* s, void* p) {
			SOCKET S = *(SOCKET*)(s);
			if (!telnetS.deLock(S).receiveFromClients(S)) telnetS.rmAdArF(S), _SOCK_CLOSE_F(S);
		} }.start(&s, NULL);
		unique_lock<mutex>lk(mut); 
		cv.wait(lk, [&] { return fl; });
	}
	uint8_t chkAdCnt = 0;
	mutex chkAdMut;
	struct chkAdStr {
		SOCKET s;
		uint8_t min;
	} chkAdAr[256];
	map<SOCKET, uint8_t> chkAdMp;
	bool rmAdAr(uint8_t n) { chkAdCnt--; while (n < chkAdCnt) chkAdAr[n] = chkAdAr[n + 1], n++; return true; }
	
	void checkAdr(uint8_t min);
};