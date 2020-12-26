#pragma once
#include "..\\ThreadCls.h"

namespace udpImplementation {
	extern void send(char* buf, int len);
	extern unsigned int receive(char* buffer, unsigned int length);
	extern mainThreadCls::strStrCnt* stringPool;

	inline void sendPrep(mainThreadCls::strSndV& s) {
		static std::mutex threadMut;
		static mainThreadCls::strMpCh mpCh;
		if (!mpCh.begin(s)) return;
		threadBufCls::recStruct{ threadMut,[](void* pMCh, void* x) {
			do [](mainThreadCls::strSndV s) { 
				send(s.pack, s.len);
				s.ret(); 
			}(((mainThreadCls::strMpCh*)pMCh)->p);
			while (!((mainThreadCls::strMpCh*)pMCh)->end());
		} }.start(&mpCh, NULL);
	}

	inline void lisBroadcast() {
		mainThreadCls::strSndV s;
		for (;;) {
			s.lsNo = stringPool->get(s.pack);
			//packet must be 0 terminated
			while (s.pack[s.len = receive(s.pack, 32)]);
			stringPool->lPosF(s.pack, s.len);
			sendPrep(s);
		}
	}
}