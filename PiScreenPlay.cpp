#include "PiScreen.h"
#include "MemFile.h"

void piScreenCls::playF(unsigned __int8 x, unsigned __int8 ad){
	if (!x) {
		lock_guard<mutex> lk(sourceWmut[ad]); shared_lock<shared_mutex> lk2(sourceMut);
		playPrep(play * 1, ad);
		return;
	} bool X = (bool)(x - 1);
	lock_guard<mutex> lk(sourceWmut[ad]); 
	lock_guard<shared_mutex> lk2(sourceMut);
	if (play == X) return; 
	if (X) {
		chanBl = true;
		unsigned long h = 0;
		sourceLen = strbasprc::charPLen(strbasprc::charPLsDR(channel = 0, source, chanPoint, h));
	}
	playPrep(2 + (play = X) * 1, ad);
	passPrep(256 + X * 256, passPrMpCha[101], 101);
}

void mainThreadCls::clsExMes::strExec::psPlayF(unsigned __int8 x, unsigned __int8 ad) {
	piScreenC.playF(x, ad);
}

void piScreenCls::playPrep(unsigned __int16 x, unsigned __int8 ad) {
	if (!passMpChaPlay.begin(x += ad * 256)) return;
	threadBufCls::recStruct{ threadCls->threadMut[ad], [](void* pMCh, void* p) {
		do ((piScreenCls*)p)->playP(((mainThreadCls::strMpCha*)pMCh)->p % 256, ((mainThreadCls::strMpCha*)pMCh)->p / 256); while (!((mainThreadCls::strMpCha*)pMCh)->end());
	} }.start(&passMpChaPlay, this);
}

void piScreenCls::playP(unsigned __int8 x, unsigned __int8 ad) {
	memFileObj fileObj(fileData);
	strncpy_s(lsPlay, 25, "Overige\\piScreenPlay.txt", 24);
	if (!fileObj.open(lsPlay)) return; 
	bool IO;
	if (x < 2) IO = (bool)(x);
	else IO = (bool)(x - 2), ad = 0;
	while (strbasprc::charPLen(strbasprc::charPLsR(lsPlay + 1, fileObj.file, fileObj.loc))) {
		unsigned __int8 adSnd = (lsPlay[3] - '0') * 10 + (lsPlay[4] - '0'), b;
		if (ad && ad - 1 != adSnd) continue;
		*lsPlay = '@';
		if (IO) lsPlay[5] = 'A', lsPlay[6] = 'N'; else lsPlay[5] = 'U', lsPlay[6] = 'T';
		lsPlay[11] = '+'; lsPlay[12] = lsPlay[(b = mpCh->len) - 2], lsPlay[13] = lsPlay[b - 1];
		mainThreadCls::trLisHomeCls* X = threadCls->sesPoint(threadCls->sesPMut + adSnd, threadCls->adresNo(adSnd));
		if (X) X->sendPrep(mainThreadCls::strSndV{ lsPlay, -13, NULL, lsNoPlay }, sendMpCh[adSnd]), lsNoPlay = mpCh->get(lsPlay);
	}
}