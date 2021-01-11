#include "ThreadCls.h"

void mainThreadCls::clsExMes::naCheckF(strSndV s, uint8_t ad, uint8_t ad2) {
	strMpCh& Po = threadCls->naCh2Mp[ad2][ad];
	if (!Po.begin(s)) return;

	threadBufCls::recStruct{
		threadCls->threadMut[ad2], [](void* pMCh, void* ad) {
		strMpCh& Po = threadCls->naChckMpCh[(uint64_t)ad];
		do {
			if (Po.begin(((strMpCh*)pMCh)->p)) 
				threadBufCls::recStruct{
				threadCls->threadMut[(uint64_t)ad], [](void* pMCh, void* p) {
				do ((strExec*)p)->naCheck(((strMpCh*)pMCh)->p, ((strMpCh*)pMCh)->ad); while (!((strMpCh*)pMCh)->end());
				} }.start(&Po, &threadCls->uitEx[(uint64_t)ad]);
		} while (!((strMpCh*)pMCh)->end());
	} }.start(&Po, (void*)(uint64_t)ad);
}


void mainThreadCls::clsExMes::strExec::naCheck(strSndV& s, uint8_t ad) {
	str = s.pack, len = s.len, sStrBuf = &s, strNow = s.lsNo;
	if (str[1] == 'u' || str[1] == 'd') len = (len + 1) * (-1);
	trLisHomeCls * x = threadCls->sesPoint(threadCls->sesPMut + ad, threadCls->adresNo(ad));
	if (x) point = x->exMes; else point = s.bron; if (passMes()) s.ret();
}

void mainThreadCls::statStrucStr::start(stSndStt st, uint8_t ad) { 
	mut.lock(); if (!ready) {
	if (lineCnt < ARSIZE_CLSMPCH) lineAr[(lineNo + lineCnt) % ARSIZE_CLSMPCH] = lAS{ val++, voeg(st, avAr[lineCnt]) }, lineCnt++;
	else mp.insert(pair<unsigned int, stSndStt>(val++, st));
	mut.unlock(); return;
	}
	ready = false, mut.unlock(), sluisS = st;
		threadBufCls::recStruct{ threadCls->threadMut[ad], [](void* st, void* p) {
		do ((stSndStt*)st)->func(); while (((statStrucStr*)p)->check());
	} }.start(&sluisS, this);
}

bool mainThreadCls::statStrucStr::check() {
	mut.lock();
	if (val != set) {
		if (lineCnt && lineAr[lineNo].cnt == set) sluisS = ar[lineAr[lineNo].no], avAr[--lineCnt] = lineAr[lineNo].no, lineNo = (lineNo + 1) % ARSIZE_CLSMPCH, set++;
		else sluisS = mp.find(set)->second, mp.erase(set++);
		mut.unlock();
		return true;
	}
	val = set = 0; ready = true;
	mut.unlock();
	return false;
}



void mainThreadCls::stSndStt::funcSnd() {
	char* ls = s.pack; int& len = s.len; uint8_t strAd = (ls[2] - '0') * 10 + (ls[3] - '0');
	for (uint8_t t = 0, m = len; t < m; t++) ls[m - t] = ls[m - 1 - t]; len++; ls[len++] = '+', *ls = '@', ls[1] = 'U', ls[2] = 'V';
	if (type == 3) {
		unsigned int wW = threadCls->statDimVar[no].load(); ls[5] = strbasprc::cv16char0(wW), ls[6] = strbasprc::cv16char1(wW);
	}
	else if (threadCls->statVar[no].load()) ls[5] = 'A', ls[6] = 'N'; else ls[5] = 'U', ls[6] = 'T';
	len = (len + 1) * (- 1);
	trLisHomeCls* x = threadCls->sesPoint(threadCls->sesPMut + strAd, threadCls->adresNo(strAd));
	if (x) x->sendPrep(s, threadCls->mpChS[strAd][strAd]);
	else s.ret();
}

void mainThreadCls::stSndStt::funcSnd2() {
	char* ls = s.pack; int& len = s.len; uint8_t strAd = (ls[3] - '0') * 10 + (ls[4] - '0');
	if (type == 5) {
		unsigned int wW = threadCls->statDimVar[no].load(); ls[5] = strbasprc::cv16char0(wW), ls[6] = strbasprc::cv16char1(wW);
	}
	else if (threadCls->statVar[no].load()) ls[5] = 'A', ls[6] = 'N'; else ls[5] = 'U', ls[6] = 'T';
	uint8_t ad2 = (ls[len] - '0') * 60 + (ls[len + 1] - '0');
	trLisHomeCls* x = threadCls->sesPoint(threadCls->sesPMut + ad2, threadCls->adresNo(strAd));
	if (x) x->sendPrep(s, threadCls->mpChS[ad2][strAd]);
	else s.ret();
}

void mainThreadCls::stSndStt::func() {
	if (type >= 2 && type < 6) { if (type >= 4) funcSnd2(); else funcSnd(); return; }

	char* buf; char* ls; int sendLen; uint8_t bufX, strAd; int8_t lsNow = p->getStr(ls), bfNow = p->getStr(buf); bool bf = false;
	if (type % 2 && type > 6 && type < 12) { if (type != 7) funcD(); }
	else if (type) threadCls->statDimVar[no].store(val); else threadCls->statVar[no].store(val);
	{
		char* chC = s.pack; 
		strncpy_s(ls, s.len + 1, s.pack, s.len);
		chC[0] = 'S', chC[1] = 'D'; for (int t = 2, m = s.len = (sendLen = s.len) - 2; t < m; t++) chC[t] = chC[t + 1];
		
		strAd = (chC[2] - '0') * 10 + (chC[3] - '0');
		trLisHomeCls* x = threadCls->sesPoint(threadCls->sesPMut + strAd, threadCls->adresNo(strAd));
		if (x) x->sendPrep({ ls, sendLen * (-1) - 1, p, lsNow }, threadCls->mpChS[strAd][strAd]);
		else p->retStr(lsNow);
	}

	while (!strbasprc::vergCharP(strbasprc::remCommCharP(strbasprc::charPLsR(buf, fl, loc)), "GG")) {
		if (buf[0] == 'P' && buf[1] == 'S') {
			sluisPiScreenF([&] {
				uint16_t V = strbasprc::cvintcharint(buf[2]) * 60 + strbasprc::cvintcharint(buf[3]);
				if (val) V += 512; else V += 256; return V;
			}(), strAd);
			continue;
		} lsNow = p->getStr(ls);
		uint8_t strAd2 = (buf[2] - '0') * 10 + (buf[3] - '0');
		if (buf[0] == 'S' && buf[1] == 'P') {
			if (!val) ledPlF(ls, lsNow, strAd2);
			else if (lsNow != 100) p->retStr(lsNow);
			else delete[] ls; continue;
		} ls[0] = '@'; strncpy_s(ls + 1, sendLen = (bufX = strbasprc::charPLen(buf)) + 1, buf, bufX); ls[sendLen++] = '+';
		if (type == 7) if (val) ls[5] = 'a', ls[6] = 'n'; else ls[5] = 'u', ls[6] = 't';
		else if (!type) if (val) ls[5] = 'A', ls[6] = 'N'; else ls[5] = 'U', ls[6] = 'T'; 
		else { unsigned int v = val; ls[5] = strbasprc::cv16char0(v), ls[6] = strbasprc::cv16char1(v); }
		trLisHomeCls* x = threadCls->sesPoint(threadCls->sesPMut + strAd, threadCls->adresNo(strAd2)); 
		if (x) x->sendPrep({ ls, sendLen * (-1) - 1, p, lsNow }, threadCls->mpChS[strAd][strAd2]);
		else if (lsNow != 100) p->retStr(lsNow); else delete[] ls;
	} s.ret();
	if (bfNow != 100) p->retStr(bfNow); else delete[] buf;
}

