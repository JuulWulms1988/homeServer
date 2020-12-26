#include "Radio.h"

mainThreadCls::radioStr& radioS = *new mainThreadCls::radioStr;

void mainThreadCls::radioStr::open() {
	for (unsigned __int8 t = 0; t < 100; t++) sendMpCh[t].ad = 100;
	strS = &threadCls->strCntS[LEDPL_CNT + 2].open(100, LEDPL_CNT + 2, 32);
	char buuuf[32];  memFileObj fileObj(fileData); unsigned __int8 dat[255];
	fileObj.open("Radio\\Set.txt"); strbasprc::charPLsR(buuuf, fileObj.file, fileObj.loc);
	while (strbasprc::charPLen(buuuf)) dat[chanCnt++] = (*buuuf - '0') * 100 + (buuuf[1] - '0') * 10 + (buuuf[2] - '0'),
			strbasprc::charPLsDR(1, buuuf, fileObj.file, fileObj.loc);
	if (!chanCnt) return;
	passStatS = new passStatStr[chanCnt]; for (unsigned __int8 t = 0; t < chanCnt; t++) passStatS[t].type = dat[t];
}

void mainThreadCls::radioStr::pass(unsigned __int16 x, unsigned __int8 ad) {
	{ lock_guard<mutex> lk(passMut[ad]); 
	if (!passMpCha.begin(x)) return; }
	threadBufCls::recStruct{ threadCls->threadMut[ad], [](void* pMCh, void* p) {
		do ((mainThreadCls::radioStr*)p)->func(((strMpCha*)pMCh)->p); while (!((strMpCha*)pMCh)->end());
	} }.start(&passMpCha, this);
}

char* mainThreadCls::radioStr::getF(char* x) {
	(shared_lock<shared_mutex>(varMut)), *x = strbasprc::cvintcharchar(radioS.chan / 60), x[1] = strbasprc::cvintcharchar(radioS.chan % 60); return x;
}

void mainThreadCls::radioStr::func(unsigned __int16 x) {
	unsigned __int8 X = x % 256;
	if (X < 100) x /= 256, passStatS[x].pass([&] { if (chan == x + 1) return 100; return 0; }() + X);
	else if ((X -= 100) < 2) 
		if (X) // radio aan
		{
			if ((!play && (play = true)) && chan) playPrep(chan, 0);
		}
		else // radio uit
		{
			if ((play && !(play = false)) && chan) playPrep(0, chan);
		}
	else if ((X -= 2) < 2)
		if (X) // chan aan
		{
			if (chan == (X = x / 256)) return;
			x = chan, varMut.lock(), chan = X, varMut.unlock();
			if (x) passStatS[x - 1].pass(256);
			if (X) passStatS[X - 1].pass(257);
			if (play) playPrep(X, x);
		}
		else // chan uit
		{
			if (chan != (x /= 256) || !x) return;
			varMut.lock(), chan = 0, varMut.unlock(); passStatS[x - 1].pass(256); if (play) playPrep(0, x);
		}
}

void mainThreadCls::radioStr::passStatStr::pass(unsigned __int16 x) {
	if (!MpCha.begin(x)) return;
	threadBufCls::recStruct{ radioS.threadMut, [](void* pMCh, void* p) {
		do ((mainThreadCls::radioStr::passStatStr*)p)->func(((strMpCha*)pMCh)->p); while (!((strMpCha*)pMCh)->end());
	} }.start(&MpCha, this);
}

void mainThreadCls::radioStr::passStatStr::func(unsigned __int16 x) {
	memFileObj fileObj(fileData); 
	strncpy_s(ls, 7, "Radio\\", 6);
	{ unsigned __int8 no = this - radioS.passStatS; ls[6] = no / 100 + '0', ls[7] = (no / 10) % 10 + '0', ls[8] = no % 10 + '0'; }
	strncpy_s(ls + 9, 5, ".txt", 4);
	if (!fileObj.open(ls)) return;
	bool IO; unsigned __int8 ad;
	if (x < 256)
		if (x < 100) IO = false, ad = x + 1;
		else IO = true, ad = x - 99;
	else IO = (bool)(x - 256), ad = 0;
	while (strbasprc::charPLen(strbasprc::charPLsR(ls + 1, fileObj.file, fileObj.loc))) {
		unsigned __int8 adSnd = (ls[3] - '0') * 10 + (ls[4] - '0'), b;
		if (ad && ad - 1 != adSnd) continue;
		*ls = '@';
		if (IO) ls[5] = 'A', ls[6] = 'N'; else ls[5] = 'U', ls[6] = 'T';
		ls[11] = '+'; ls[12] = ls[(b = radioS.strS->len) - 2], ls[13] = ls[b - 1];
		mainThreadCls::trLisHomeCls* X = threadCls->sesPoint(threadCls->sesPMut + adSnd, threadCls->adresNo(adSnd));
		if (X) X->sendPrep(mainThreadCls::strSndV{ ls, -13, NULL, lsNo }, radioS.sendMpCh[adSnd]), lsNo = radioS.strS->get(ls);
	}
}

void mainThreadCls::radioStr::playPrep(unsigned __int8 x, unsigned __int8 old) {
	{ unsigned __int16 X = x * 256 + old; if (!MpCha.begin(X)) return; }
	threadBufCls::recStruct{ radioS.threadMut, [](void* pMCh, void* p) {
		do ((mainThreadCls::radioStr*)p)->playF(((strMpCha*)pMCh)->p / 256, ((strMpCha*)pMCh)->p % 256); while (!((strMpCha*)pMCh)->end());
	} }.start(&MpCha, this);
}

void mainThreadCls::radioStr::playF(unsigned __int8 x, unsigned __int8 old) {
	if (old && passStatS[old - 1].type == 1) connSoundPiF(false);
	killProc("chrome.exe");
	if (x) switch (passStatS[x - 1].type) {
	case 0: system([&](char* BB) {
			memFileObj fileObj(fileData); fileObj.open("Radio\\Set.txt");
			strncpy_s(BB + 71 + strbasprc::charPLen(strbasprc::charPLsDR(1 + ((x - 1) * 2), BB + 71, fileObj.file, fileObj.loc)), 2, "\"", 1); return BB;
		} (threadCls->radBuf));	break;
	case 1: connSoundPiF(true); break;
	}
}

void mainThreadCls::trLisHomeCls::timedRadF(char* x) {
	unsigned __int8 theAd = adrs.load();
	if (theAd != 255 && ((x[2] == 'A' && x[3] == 'N') || (x[2] == 'U' && x[3] == 'T'))) [&](bool A) {
		if (A) radioS.pass(101 - x[2] / 'U', theAd);
	} (timedComNoStr::get(timedComNo, threadCls->timedComNoS[theAd]).appr);
}