#pragma once
#include "ServerTelnet.h"
#include "threadCls.h"
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
			if (!telnetS.deLock(S).receiveFromClients(S)) telnetS.rmAdArF(S), closesocket(S);
		} }.start(&s, NULL);
		cv.wait(unique_lock<mutex>(mut), [&] { return fl; });
	}
	unsigned __int8 chkAdCnt = 0;
	mutex chkAdMut;
	struct chkAdStr {
		SOCKET s;
		unsigned __int8 min;
	} chkAdAr[256];
	map<SOCKET, unsigned __int8> chkAdMp;
	bool rmAdAr(unsigned __int8 n) { chkAdCnt--; while (n < chkAdCnt) chkAdAr[n] = chkAdAr[n + 1], n++; return true; }
	
	void checkAdr(unsigned __int8 min);
};


