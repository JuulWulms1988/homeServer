#include "ledPlaf.h"

void mainThreadCls::clsExMes::strExec::sendLedPl(uint8_t ad) {
	clsLedPl::clsLedPlObj& p = *p_ledPl.toObjF(strAd);
	p.passPrep(	{ ls, sendLen, point, lsNow }, threadCls->mpChS[ad][99 + p.no], ad), lsNow = point->getStr(ls);
	sendLen = 0;
}

void mainThreadCls::clsLedPl::clsLedPlObj::passPrep(strSndV s, strMpCh& pMCh, uint8_t ad) {
	if (!pMCh.begin(s)) return;
	threadBufCls::recStruct{ threadCls->threadMut[ad], [](void* pMCh, void* p) {
		do ((clsLedPlObj*)p)->pass(((strMpCh*)pMCh)->p); while (!((strMpCh*)pMCh)->end());
	} }.start(&pMCh, this);
}
void mainThreadCls::clsLedPl::clsLedPlObj::pass(strSndV& s) {
	if (!passMp.begin(s)) return;
	threadBufCls::recStruct{ p_ledPl.threadMut, [](void* pMCh, void* p) {
		do ((clsLedPlObj*)p)->ledPlFunc(((strMpCh*)pMCh)->p); while (!((strMpCh*)pMCh)->end());
	} }.start(&passMp, this);
}

void mainThreadCls::clsLedPl::clsLedPlObj::psMsPr() {
	{
		{
			unsigned int l = 0;
			for (uint8_t t = 0; t < 6; t++) {
				unsigned long in;
				switch (t) {
				case 0: upM.store(in = p_clstijd->maand.load()); break;
				case 1: upD.store(in = p_clstijd->dag.load()); break;
				case 2: upU.store(in = p_clstijd->uur.load()); break;
				case 3: upMi.store(in = p_clstijd->minuut.load()); break;
				case 4: upS.store(in = p_clstijd->seconde.load()); break;
				case 5: in = upN.load(); if (!++in) upN.store(in = 1); else upN.store(in); break;
				}
				bufPsMs[(l += strbasprc::cvcharlngth(60, in, bufPsMs + l))++] = '\\';
			} 
			char* lS = sndS.pack; int& L = sndS.len;
			for (unsigned int t = L - 1; t != 0; t--) lS[t + l] = lS[t];
			L += l; for (unsigned int t = 0; t < l; t++) lS[t + 1] = bufPsMs[t];
		}
		mpCh.lPosF(sndS.pack, sndS.len); bool x; unique_lock<mutex> lk(cvPsMs.mut); cvPsMs.ready = !(x = cvPsMs.ready);
		if (!x) { cvPsMsBl = false, cvPsMs.cv.wait(lk, [&] { return cvPsMsBl; }); sndS.len = 0, sndS.bron = NULL, sndS.lsNo = mpCh.get(sndS.pack); return; }
	} progS = sndS;
	threadBufCls::recStruct{ p_ledPl.threadMut, [] (void* p, void* U){
		((clsLedPlObj*)p)->progPsMs();
	} }.start(this, NULL), sndS.len = 0, sndS.bron = NULL, sndS.lsNo = mpCh.get(sndS.pack);
}

void mainThreadCls::trLisHomeCls::chSerAggPl(uint8_t adrB) {
	clsLedPl::clsLedPlObj& ldP = *p_ledPl.toObjF(adrB);
	ldP.passPrep(strSndV{ NULL }, threadCls->mpChS[adrB][99 + ldP.no], adrB);
}

void mainThreadCls::clsLedPl::clsLedPlObj::flagPsMsPr() {
	{
		unique_lock<mutex> lk(cvPsMs.mut); cvPsMs.cv.wait(lk, [&] { return cvPsMs.ready; });
		cvPsMs.ready = false;
	} threadBufCls::recStruct{ p_ledPl.threadMut, [](void * p, void* U) { ((clsLedPlObj*)p)->flagPsMs();} }.start(this, NULL);
}

void mainThreadCls::stSndStt::ledPlF(char* ls, int8_t lsNow, uint8_t strAd) {
	*ls = 'E'; clsLedPl::clsLedPlObj& P = *p_ledPl.toObjF(strAd);
	P.passPrep({ ls, 1, p, lsNow }, threadCls->mpChS[strAd = p->pLisHome->adrs][99 + P.no], strAd);
}

void mainThreadCls::clsLedPl::clsLedPlObj::empPsMsPr() {
	{
		unique_lock<mutex> lk(cvPsMs.mut); cvPsMs.cv.wait(lk, [&] { return cvPsMs.ready; });
		cvPsMs.ready = false;
	} threadBufCls::recStruct{ p_ledPl.threadMut, [](void * p, void* U) { ((clsLedPlObj*)p)->empPsMs();} }.start(this, NULL);
}

void mainThreadCls::clsLedPl::clsLedPlObj::psMsPr2(strSndV& s) {
	trLisHomeCls* ppp = threadCls->sesPoint(threadCls->sesPMut + adr, threadCls->adresNo(adr));
	if (ppp) ppp->sendPrep(s, threadCls->mpChS[adr][adr]);
	else s.ret();
}

void mainThreadCls::clsLedPl::clsLedPlObj::voegFrCons(strSndV s, uint8_t ad) {
	if (!voegMpCh.begin(s)) return;
	threadBufCls::recStruct{ threadCls->threadMut[ad], [](void* pMCh, void* p) {
		do ((clsLedPlObj*)p)->voegF(((strMpCh*) pMCh)->p); while (!((strMpCh*)pMCh)->end());
	} }.start(&voegMpCh, this);
}

void mainThreadCls::clsLedPl::clsLedPlObj::voegF(strSndV &s) {
	char thisChar; for (int t = 0, m = s.len; t < m; t++) 
	if ((thisChar = s.pack[t]) == '$') passPrep(strSndV{ NULL }, threadCls->mpChS[adr][99 + no], adr); 
	else if (thisChar == '\n') voegS.voegChar(thisChar), voegS.voegChar('+'), voegS.bron = s.bron, voegS.len = 1; 
	else if (voegS.voegChar(thisChar) > 512) voegS.len = 1; s.ret();
}

void mainThreadCls::clsExMes::strExec::voegLedPlaf(uint8_t ad) {
	clsLedPl::clsLedPlObj& p = *p_ledPl.toObjF((str[2] - '0') * 10 + (str[3] - '0'));
	if (str[4] == '&') *ls = 'R', strncpy_s (ls + 1, sendLen = len - 4, str + 5, sendLen - 1), p.passPrep(strSndV{ ls, sendLen, point, lsNow }, threadCls->mpChS[ad][p.no], ad);
	else strncpy_s(ls, len - 3, str + 4, sendLen = len - 4), p.voegFrCons(strSndV{ ls, sendLen, point, lsNow }, ad);
	lsNow = point->getStr(ls), sendLen = 0;
}