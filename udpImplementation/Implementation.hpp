#pragma once
#include "../ThreadCls.h"

namespace udpImplementation {
	extern void send(char* buf, int len);
	extern unsigned int receive(char* buffer, unsigned int length);
	extern mainThreadCls::strStrCnt* stringPool;

	inline void sendPrep(mainThreadCls::strSndV s) {
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
		char* x, lsN; int l;
		for (;;) {
			lsN = stringPool->get(x);
			//packet must be 0 terminated
			while (x[l = receive(x, 32)]);
			stringPool->lPosF(x, l);
			sendPrep(mainThreadCls::strSndV{x, l, NULL, lsN});
		}
	}
}