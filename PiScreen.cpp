#include "PiScreen.h"

piScreenCls& piScreenC = *new piScreenCls;

void piScreenCls::start() {
	mpCh = &threadCls->strCntS[LEDPL_CNT + 1].open(100, LEDPL_CNT + 1, 32);
	lsNoPlay = mpCh->get(lsPlay);
	char buuuf[512]; memFileObj fileObj(fileData);
	{
		fileObj.open("Overige\\piScreen.txt"); clientCnt = 0; while (!strbasprc::vergCharP(strbasprc::charPLsR(buuuf, fileObj.file, fileObj.loc), "AA")) clientCnt++; fileObj.loc = 0;
		screenObj = new screenObjS[clientCnt + 1]; for (unsigned __int8 t = 0; t <= clientCnt; t++) screenObj[t].sBuf = new char[([&] { if (!t) return 519; return 15; })()];
		unsigned __int8 t = 0; while (!strbasprc::vergCharP(strbasprc::charPLsR(buuuf, fileObj.file, fileObj.loc), "AA")) screenObj[++t].set(buuuf, strbasprc::charPLen(buuuf));
	}
	screenObj[0].adr = (strbasprc::charPLsR(buuuf, fileObj.file, fileObj.loc)[0] - '0') * 10 + (buuuf[1] - '0');
	{
		int uitpr;
		for (unsigned __int8 t = 1; *strbasprc::charPLsR(buuuf, fileObj.file, fileObj.loc) && t <= clientCnt; t++)
			if (threadCls->statVar[uitpr = (*buuuf - '0') * 100 + (buuuf[1] - '0') * 10 + (buuuf[2] - '0') - 100].load()) pass(t + 512);
	}
	if (play) pass(512);
	for (unsigned __int8 t = 0; t <= clientCnt; t++) screenObj[t].sendMpCh.ad = screenObj[t].adr;
	chanPoint = fileObj.file + fileObj.loc;
	for (unsigned long t = 0, l = 0; *strbasprc::charPLsR(buuuf, chanPoint, l) || ((t /= 2) && !(chanCnt = t)); t++);
}

void piScreenCls::chanF(unsigned __int16 no, unsigned __int8 ad) {
	bool Niet = true;
	{
		lock_guard<mutex> lk(sourceWmut[ad]); lock_guard<shared_mutex> lk2(sourceMut);
		if (chanBl)
			if (no == channel && play) return;
			else if (no > 255)
				if (!play) channel = 0;
				else if (no == 256)
					if (!channel) channel = chanCnt - 1;
					else channel--;
				else channel = (channel + 1) % chanCnt;
			else channel = no;
		else if ((chanBl = true) && (no < 256 || (channel = 0))) channel = no;
		unsigned long h = 0;
		sourceLen = strbasprc::charPLen(strbasprc::charPLsDR(channel * 2, source, chanPoint, h));
		if (!play) playPrep(2 + (play = !(Niet = false)) * 1, ad), passPrep(512, passPrMpCha[101], 101);
	} if (Niet) passPrep(0, passPrMpCha[ad], ad);
}

bool piScreenCls::StreamVidVar(char* x) {
	shared_lock<shared_mutex> lk(piScreenC.sourceMut);
	if ((!piScreenC.play && (x[0] = x[1] = '0')) || (chanBl && (x[0] = strbasprc::cvintcharchar((channel + 1) / 60)) && (x[1] = strbasprc::cvintcharchar((channel + 1) % 60)))) return false;
	strncpy_s(x, sourceLen - 1, source, sourceLen - 2); return true;
}

void piScreenCls::func(unsigned __int16 s) {
	unsigned __int16 yoyo;
	switch (s / 256) {
	case 0: connectF(s % 256); break;
	case 3: statMut.lock_shared(), yoyo = statCnt, statMut.unlock_shared(), serverIO(yoyo); break;
	default: statF((s / 256) - 1, s % 256); break;
	}
}

void ServerTelnet::accept_piScreen(unsigned int clNo, SOCKET clSock) {
	if (clNo > piScreenC.clientCnt) { closesocket(clSock); return; } 
	{
		piScreenCls::screenObjS& p = piScreenC.screenObj[clNo];
		p.sockConMut.lock();
		if (p.connected && p.sock != clSock) closesocket(p.sock);
		p.connected = true, p.sock = clSock; p.sockConMut.unlock();
	}
	piScreenC.pass(clNo);
	for (char t = 1, w; (NetworkServices::receiveMessage(clSock, &w, 1) <= 0 && t < 16) || (t < 16 && !(t = 0)); t++);
	piScreenCls::screenObjS& p = piScreenC.screenObj[clNo];
	p.sockConMut.lock();
	if (p.connected && p.sock == clSock) closesocket(clSock), p.connected = false;
	p.sockConMut.unlock();
}

void piScreenCls::pass(unsigned __int16 s) {
	if (!passMpCha.begin(s)) return;
	threadBufCls::recStruct{ telnetS.tMut, [](void* pMCh, void* p) {
		do ((piScreenCls*)p)->func(((mainThreadCls::strMpCha*)pMCh)->p); while (!((mainThreadCls::strMpCha*)pMCh)->end());
	} }.start(&passMpCha, this);
}



void piScreenCls::passPrep(unsigned __int16 s, mainThreadCls::strMpCha& mapCh, unsigned __int8 ad) {
	if (!mapCh.begin(s)) return;
	mutex* P; if (ad == 100) P = &telnetS.tMut; else if (ad == 101) P = &threadMut; else P = threadCls->threadMut + ad;
	threadBufCls::recStruct{ *P, [](void* pMCh, void* p) {
		do ((piScreenCls*)p)->pass(((mainThreadCls::strMpCha*)pMCh)->p); while (!((mainThreadCls::strMpCha*)pMCh)->end());
	} }.start(&mapCh, this);
}

void mainThreadCls::sluisPiScreenF(unsigned __int16 s, unsigned __int8 ad) {
	piScreenC.passPrep(s, piScreenC.passPrMpCha[ad], ad);
}

void mainThreadCls::clsExMes::strExec::sluisPiScreenFC() {
	unsigned __int8 aDD = point->pLisHome->adrs.load();
	piScreenC.chanF(strbasprc::cvintcharint(buf[2]) * 60 + strbasprc::cvintcharint(buf[3]), aDD);
}

void extCls::piSWrite(unsigned __int8 i, char* x) {
	switch (i) {
	case 0: piScreenC.channel = strbasprc::cvintcharint(*x) * 60 + strbasprc::cvintcharint(x[1]); return;
	case 1: if (*x - '0') piScreenC.chanBl = true; else piScreenC.chanBl = false; return;
	case 2: piScreenC.sourceLen = strbasprc::cvintcharint(*x) * 60 + strbasprc::cvintcharint(x[1]); return;
	case 3: { char* p = piScreenC.source; while (*(p++) = *(x++)); return; }
	}
}

void* extCls::piSRead(unsigned __int8 i) {
	switch (i) {
	case 0: piScreenC.sourceMut.lock_shared(); return (void*)piScreenC.channel;
	case 1: if (piScreenC.chanBl) return (void*)(true); return NULL;
	case 2: return (void*)piScreenC.sourceLen;
	case 3: return piScreenC.source;
	case 4: piScreenC.sourceMut.unlock_shared(); return NULL;
	}
}

bool extCls::piSPlay(__int8 x) {
	if (x) { piScreenC.play = (bool)(x -= 1); return x; }
	shared_lock<shared_mutex> lk(piScreenC.sourceMut); return piScreenC.play;
}