#include "ThreadCls.h"
#include <thread>
extern ServerGame* server;
extern unsigned int balans;
extern unsigned __int8 adres[100];
extern map<unsigned int, string> leesclient;

extern char* charPrint(unsigned int x, string& a);
extern void printTijdel(char** p, unsigned int l);

namespace udpImplementation {
	mainThreadCls::strStrCnt* stringPool;
}

void TH_FFVOOrtijd(SOCKET* ClientSocket) {
	strCv* cv = &threadCls->cvAcc;
	{ unique_lock<mutex> lk(cv->mut);
	cv->cv.wait(lk, [&] {return cv->ready; }); if (threadCls->sesFull) return; cv->ready = false; }
	thread ([](SOCKET s) { threadCls->trAcc(&s); }, *ClientSocket).detach();
}

mainThreadCls::mainThreadCls() {
	p_TrBC.open();
	webLisHome.adrs.store(99);
	for (unsigned __int8 t = 0; t < 100; t++) mpChS[t] = new strMpCh[100 + LEDPL_CNT];
	strCntS = new strStrCnt[3 + LEDPL_CNT];
	//Udp
	(udpImplementation::stringPool = strCntS)->open(100, 0, 32);
	for (unsigned __int8 t = 0; t < 100; t++) { for (unsigned __int8 tt = 0; tt < 100; tt++) mpChS[t][tt].ad = tt; naChckMpCh[t].ad = t, uitEx[t].set(NULL, 255); }
	for (unsigned __int8 t = 0; t < 100; t++) adress[t] = 255;
	delay = false, accHome = new trLisHomeCls, newSes(), threadCls = this, openLdPl();
	extCls::begin();
	thread([] { ((mainThreadCls::deBootStr*)bootPtrAlg)->subF(); server->network->acceptNewClient(); }).detach();
}

unsigned int mainThreadCls::strStrCnt::lPosObNoF(char* x, unsigned int l, bool type) {
	unsigned int uit = strbasprc::cvintcharint(x[l]) * 60 + strbasprc::cvintcharint(x[l + 1]), len = threadCls->strCntS[uit].len; 
	if (!type) return len; for (unsigned __int8 t = 0; t < 2; t++) x[len - 2 + t] = x[l + t]; return uit;
}

mainThreadCls::trLisHomeCls::trLisHomeCls() {
	strLen = sendSet = strAanv = sendVal = 0; adrs = 255; available = close = lsAr = del = false;
	closeMut = sendReady = true;
}

mutex ffMut;

void mainThreadCls::trLisHomeCls::loop(SOCKET* sock) {
	socket = *sock; lpStr = ls[(lsAr = !lsAr) * 1]; __int8 clsCntLis = 0; while (true) {
		if ((iResult = NetworkServices::receiveMessage(socket, lpStr, 1000)) <= 0 || del.load())
		{
			if (!del.load()) if (clsCntLis++ < 14) continue;
			else closeF(); unsigned __int8 buf;
			threadCls->sesPDMut.lock(); threadCls->sMutSes.lock(); { if ((buf = adrs.load()) != 255)
			{ threadCls->sMutAdr.lock(); if (threadCls->adress[buf] == mpSesNo.load()) threadCls->adress[buf] = 255; threadCls->sMutAdr.unlock(); }
			else threadCls->voegAdr(mpSesNo.load());
			} threadCls->ses.erase(mpSesNo.load()); threadCls->sMutSes.unlock(); threadCls->sesPDMut.unlock();
			cvClose.wait(unique_lock<std::mutex>(muClose), [&] {return closeMut; });
			{ strCv* sP = &threadCls->cvAccFull; { unique_lock<mutex> lk2(sP->mut); if (sP->ready) sP->ready = false; } sP->cv.notify_one(); }
			cvLis.cv.wait(unique_lock<mutex>(cvLis.mut), [&] { return cvLis.ready; });
			if (exNow == 100) delete[32] mesStr; else exMes->retStr(exNow);
			Sleep(10000); delete exMes; ffMut.lock(); cout << "Delete: " << (int)buf << '\n'; ffMut.unlock(); delete this; return;
		}
		if (clsCntLis) clsCntLis = 0;
	cvLis.cv.wait(unique_lock<mutex>(cvLis.mut), [&] { return cvLis.ready; }), cvLis.ready = false;
	thread ([](trLisHomeCls* pTh, char* msg, int len) {
		pTh->messPr(msg, len); strCv& x = pTh->cvLis;
		(unique_lock<mutex>(x.mut)), x.ready = true; x.cv.notify_one();
	}, this, lpStr, iResult).detach();
	lpStr = ls[(lsAr = !lsAr) * 1];
	}
}

/*
bool mainThreadCls::strMpCh::begin(strSndV& s) {
	mut.lock();
	if (ready) { ready = false; mut.unlock(); p = s; return true; }
	mp.insert(pair<unsigned int, strSndV>(val++, { s }));
	mut.unlock();
	return false;
}

bool mainThreadCls::strMpCh::end() {
	lock_guard<mutex> lk(mut);
	if (val != set) {
		p = mp.find(set)->second;
		mp.erase(set++); 
		return false;
	}
	val = set = 0; ready = true; 
	return true;
}
*/
void mainThreadCls::trLisHomeCls::sendPrep(strSndV s, strMpCh& pMCh) {
	if (!pMCh.begin(s)) return;
	threadBufCls::recStruct{ threadCls->threadMut[pMCh.ad],[](void* pMCh, void* p) {
		do ((trLisHomeCls*)p)->send(((strMpCh*)pMCh)->p, 0); while (!((strMpCh*)pMCh)->end());
	} }.start(&pMCh, this);
}

void mainThreadCls::trLisHomeCls::send(strSndV& s, unsigned __int8 ad) {
	mutSend.lock();
	if (del.load()) { mutSend.unlock(); chSerAgg(s); s.ret(); return; }
	if (!sendReady) {
		if (sndlineCnt < ARSIZE_CLSMPCH) sndlineAr[(sndlineNo + sndlineCnt) % ARSIZE_CLSMPCH] = lAS{ sendVal++, sndvoeg(s, sndavAr[sndlineCnt]) }, sndlineCnt++;
		else sendMp.insert(pair<unsigned int, strSndV>(sendVal++, { s }));
		mutSend.unlock();
		return;
	} sendReady = false, mutSend.unlock(), sndSStr = s;
	threadBufCls::recStruct{ threadCls->threadMut[adrs.load()], [](void* p, void* s) {
		((trLisHomeCls*)p)->sendPr();
	} }.start(this, NULL);
}

void mainThreadCls::trLisHomeCls::chSerAgg(strSndV& s) {
	if (*s.pack != '$') return; char * sP = s.pack; int sL = s.len + 2;
	unsigned __int8 adrB = sP[sL + 1] / 10 + sP[sL + 2] % 10;
	switch (sP[sL]) {
	case 0: chSerAggPl(adrB); break;
	}
}

void mainThreadCls::strSndV::ret() {
	if (len < 0) len = (len + 1) * (-1);
	if (lsNo == 100) { delete[32] pack; }
	else if (lsNo >= 0) bron->retStr(lsNo); 
	else if (lsNo == -101) delete[strStrCnt::lPosObNoF(pack, len, false)] pack; 
	else threadCls->strCntS[strStrCnt::lPosObNoF(pack, len, true)].ret(lsNo);
}

extern mutex ffMut;

void mainThreadCls::trLisHomeCls::sendPr() {
	(lock_guard<mutex>(muClose)), closeMut = false; __int8 clsCntSnd = 0;
	while (true) { 
		bool neg; if (sndSStr.len < 0) neg = true, sndSStr.len = (sndSStr.len + 1) * (-1); else neg = false;
		//do {
		//	char* ii = sndSStr.pack;
		//	char i = ii[1]; if ((i == 't' || i == 'T') && ((i = ii[2]) == 't' || i == 'T' || i == 'u' || i == 'U')) break;
	//		char k[512]; char *kk = sndSStr.pack; for (int t = 0, m = sndSStr.len; t < m; t++) k[t] = kk[t]; k[sndSStr.len] = '\0';
	//		ffMut.lock(), cout << "Send (" << (int)adrs.load() << "): " << k << '\n', ffMut.unlock();
	//	} while (false); 
		if (del.load() || NetworkServices::sendMessage(socket, sndSStr.pack, sndSStr.len) == SOCKET_ERROR) {
			if (!del.load()) if (clsCntSnd++ < 14) continue; else closeF();
			if (neg) sndSStr.len = sndSStr.len * (-1) - 1; chSerAgg(sndSStr); sndSStr.ret(); mutSend.lock();
			while (sendVal != sendSet) 
				if (sndlineCnt && sndlineAr[sndlineNo].cnt == sendSet) sndar[sndlineAr[sndlineNo].no].ret() , sndavAr[--sndlineCnt] = sndlineAr[sndlineNo].no, sndlineNo = (sndlineNo + 1) % ARSIZE_CLSMPCH, sendSet++;
				else sendMp.find(sendSet)->second.ret(), sendMp.erase(sendSet++);
			mutSend.unlock();
			(lock_guard<mutex>(muClose)), closeMut = true; cvClose.notify_one(); return;
		}// if (adrs == 1){
			//char hhh[512]; int t = 0, m = s.len; for (char* ppp = s.pack; t < m; t++) hhh[t] = ppp[t]; hhh[m] = '\0';
			//char *c[2]{ "Send 1: ", hhh }; printTijdel(c, 2);
		//}
		
		if (clsCntSnd) clsCntSnd = 0;
		if (neg) sndSStr.len = sndSStr.len * (-1) - 1; sndSStr.ret();
		mutSend.lock();
		if (sendVal != sendSet) {
			if (sndlineCnt && sndlineAr[sndlineNo].cnt == sendSet) sndSStr = sndar[sndlineAr[sndlineNo].no], sndavAr[--sndlineCnt] = sndlineAr[sndlineNo].no, sndlineNo = (sndlineNo + 1) % ARSIZE_CLSMPCH, sendSet++;
			else sndSStr = sendMp.find(sendSet)->second, sendMp.erase(sendSet++);
		} else { sendReady = true, mutSend.unlock(), (unique_lock<mutex>(muClose)), closeMut = true; cvClose.notify_one(); return; }
		mutSend.unlock();
	}
}

mainThreadCls::strStrCnt& mainThreadCls::strStrCnt::open(__int8 c, unsigned int n, unsigned int l) {
	ls = new char[(cnt = lsT = c) * (len = (l += 2))];
	{ char y[2]; unsigned __int8 yL = strbasprc::cvcharlngth(60, no = n, y); for (unsigned int t = 0; t < c; t++) { char* Y = ls + (l - 2) + l * t; if (yL == 2) *Y = y[0]; else *Y = '0'; Y[1] = y[yL - 1]; } }
	lsA = new __int8[c]; for (__int8 t = 0, z = c - 1; t < c; t++) lsA[t] = z--; return *this;
}

__int8 mainThreadCls::strStrCnt::get(char*& x) {
	{
		lock_guard<mutex> lk(mut);
		if (lsT) { __int8 y; x = ls + ((y = lsA[--lsT]) * len); 
		return -y - 1; }
	} x = new char[len];
	{ char y[2]; unsigned __int8 yL = strbasprc::cvcharlngth(60, no, y); char* Y = x + (len - 2); if (yL == 2) *Y = y[0]; else *Y = '0'; Y[1] = y[yL - 1];  }
	return -101;
}

void mainThreadCls::clsExMes::strExec::set(clsExMes* p, __int8 x) {
	if (p) pExMp = &(point = p)->exCls;
	fileObj.openStr("", fileData); if (x != 255) ls = p->lsP + (lsNow = x) * 32;
}

void mainThreadCls::clsExMes::exStr::voeg(var& s) {
	mut.lock();
	if (iT) {
		com = 0, iT--, threadBufCls::recStruct{ threadCls->threadMut[point->pLisHome->adrs.load()],[](void * p, void* s) {
	((strExec*)p)->start(); } }.start(
	   [&](strExec* p) { p->strVarS = s, mut.unlock(); return p; }(&i[([&] {__int8 UU = iNo; iNo = (iNo + 1) % 20; return UU; }())]), NULL);
		return;
	}
	else if (s.type > 0) 
		if (lineCnt < ARSIZE_CLSMPCH) lineAr[(lineNo + lineCnt) % ARSIZE_CLSMPCH] = lAS{ valS++, voegf(s, avAr[lineCnt]) }, lineCnt++;
		else mpS.insert(pair<unsigned int, var>(valS++, { s }));
	else 
		if (lineCntf < ARSIZE_CLSMPCH) lineArf[(lineNof + lineCntf) % ARSIZE_CLSMPCH] = lAS{ valF++, voegff(s, avArf[lineCntf]) }, lineCntf++;
		else mpF.insert(pair<unsigned int, var>(valF++, { s }));
	mut.unlock();
}

void mainThreadCls::clsExMes::strExec::start() {
	do { str = strVarS.x, len = strVarS.len, strNow = strVarS.lsNow;
	switch (strVarS.type) {
	case -3: actionWFunc(); break;
	case -2: actionFunc(); break;
	case -1: passMes(); break;
	case 0: main(); break;
	case 1: stReq(); break; } }
	while (pExMp->ret(strVarS, now));
}

bool mainThreadCls::clsExMes::exStr::ret(var& s, __int8 n) {
	mut.lock(); 
	if (s.lsNow == 100) delete[32] s.x;
	else point->retStr(s.lsNow);
	if (!avail()) { __int8 x; 
		if ((x = iNo + iT++ - 20) < 0) x += 20; 
		iA[x] = n; mut.unlock(); cv.notify_one(); 
		return false; 
	}
	if ((com && !(com = false)) || !diff(true)) {
		if (lineCnt && lineAr[lineNo].cnt == setS) s = ar[lineAr[lineNo].no], avAr[--lineCnt] = lineAr[lineNo].no, lineNo = (lineNo + 1) % ARSIZE_CLSMPCH, setS++;
		else s = mpS.find(setS)->second, mpS.erase(setS++);
	}
	else {
		com = comF(); 
	if (lineCntf && lineArf[lineNof].cnt == setF) s = arf[lineArf[lineNof].no], avArf[--lineCntf] = lineArf[lineNof].no, lineNof = (lineNof + 1) % ARSIZE_CLSMPCH, setF++;
	else s = mpF.find(setF)->second, mpS.erase(setF++);
	}
	mut.unlock(); return true;
}