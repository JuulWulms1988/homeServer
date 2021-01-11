#include "nSite.h"

clswbusr2& p_wUsr = *new clswbusr2();
clsNSite* p_nSite;

void clsNSite::main(SOCKET& s) {
	cntMut.lock(); 
	if (!cnt) {
		for (int t = 0; t < lineCnt; t++) if (ar[lineAr[(lineNo + t) % ARSIZE_CLSMPCH].no] == s) { cntMut.unlock(); return; };
		for (map<unsigned int, SOCKET>::iterator t = cntMp.begin(); t != cntMp.end(); t++) if (t->second == s) { cntMut.unlock(); return; };
		if (lineCnt < ARSIZE_CLSMPCH) lineAr[(lineNo + lineCnt) % ARSIZE_CLSMPCH] = lAS{ cntVal++, voeg(s, avAr[lineCnt]) }, lineCnt++;
		else cntMp.insert(pair<unsigned int, SOCKET>(cntVal++, s));
	}
	else threadBufCls::recStruct{ threadMut, [](void* AA, void* n) {
		p_nSite->start((uint64_t)n);
	} }.start(NULL, [&] { uint8_t U = cntAr[--cnt]; p_nSite->fncCls[U].sluisSock = s; return (void*)(uint64_t)U; }());
	cntMut.unlock();
}

clsNSite::clsNSite() {
	p_nSite = this; 
	for (char t = 0, p = '\0'; t < 100; t++) fncCls[t].fileObj.openStr(&p, fileData);
	threadCls->tijdProc(); getStr.open(100, 0, SENDLEN_INT);
	for (int8_t t = 0; t < 100; t++) cntAr[t] = t;
	((mainThreadCls::deBootStr*)bootPtrAlg)->subF();
	network->acceptNewClient();
}

void clsNSite::start(int8_t n) {
	do {
		{ lock_guard<mutex> lk(mutChkAd); 
		mpChkAdAr[n] = (p_clstijd->minuut.load() + 1) % 60;
		chckAd.store(true); }
		(fncCls[n].proc()); 
		cntMut.lock(); 
		if (cntVal != cntSet) {
			if (lineCnt && lineAr[lineNo].cnt == cntSet) fncCls[n].sluisSock = ar[lineAr[lineNo].no], avAr[--lineCnt] = lineAr[lineNo].no, lineNo = (lineNo + 1) % ARSIZE_CLSMPCH, cntSet++;
			else fncCls[n].sluisSock = cntMp.find(cntSet)->second, cntMp.erase(cntSet++);
			cntMut.unlock();
		}
	else break; } while (true); cntAr[cnt++] = n, cntMut.unlock();
}

void ServerintNetwork::accF() {
	p_nSite->main(ClientSocket);
}

void mainThreadCls::exMesOne:: chckSiteAd() {
	if (p_nSite->chckAd.load()) p_nSite->checkAdr(p_clstijd->minuut.load());
}

void clsNSite::checkAdr(uint8_t min) {
	if (!min) min = 59; else min--;
	blArdChk[0] = blArdChk[1] = 0;
	lock_guard<mutex> lk(mutChkAd);
	bool uit = true;
	for (uint8_t t = 0, w; t < 100; t++) if (mpChkAdAr[t] && ((w = mpChkAdAr[t]) <= min || w > min + 2))
		mpChkAdAr[t] = 0, uit = false, fncCls[t].closeF2();
	if (uit) chckAd.store(false);
}

void clsNSite::voegAdr(func* f) {
	lock_guard<mutex> lk(mutChkAd);
	mpChkAdAr[f - fncCls] = 0;
}

void clsNSite::func::proc() {
	sock = &sluisSock; len = 0; lsNo = p_nSite->getStr.get(ls); getPost = 0; del.store(false); outFF = true; bool flag, flag2, flag1 = flag2 = flag = false;
	do {
		if (_SOCK_RESULT_COMP((lsLen = NetworkServices::receiveMessage(sluisSock, get + len, GETLEN_INT - len)))) break; else len += lsLen;
		switch (getPost) {
		case 0:
			if (len < 5) break;
			if (*get == 'G' && get[1] == 'E' && get[2] == 'T' && get[3] == ' ' && get[4] == '/') getPost = 1;
			else if (*get == 'P' && get[1] == 'O' && get[2] == 'S' && get[3] == 't' && get[4] == ' ' && ((len == 5 && !(getPost = 1)) || get[5] == '/')) getPost = 2;
			else if (getPost) getPost = 0;
			else if (!del.load()) closeF();
			if (!getPost) break;
		case 1:
			if (len != GETLEN_INT) {
				lsLen = len - lsLen; {
					bool flag3 = false; while (!flag3 && lsLen != len) switch (get[lsLen++]) {
					case '\r': if (flag2) flag3 = true; else flag = true; break;
					case '\n': if (flag2) flag3 = true; else if ((flag2 = true) && flag) flag = false; break;
					default: if (flag) flag = false, flag2 = true; break;
					}
					if (flag3) outFF = false, p_nSite->voegAdr(this), flag1 = true, lsLen = 0, getLsPrc();
				}
			}
			else if (!del.load()) closeF();
			break;
		case 2:
			closeF(); flag1 = true; break;
		}
	} while (outFF && !del.load());
	if (!flag1) p_nSite->voegAdr(this);
	if (lsLen && !(_SOCK_ENUM_COMP(lsLen, SOCKET_ERROR))) send(); else if (lsNo == -101) delete[] ls; else p_nSite->getStr.ret(lsNo);
	mpCh.wait(cvMpCh); if (!del.load()) _SOCK_CLOSE_F(*sock);
}

void clsNSite::func::voeg(const char* x, unsigned int y) {
	do {
		unsigned int q; bool z = false;
		if (y < (q = SENDLEN_INT - lsLen)) z = true, q = y; { char* v = ls + lsLen;
		for (unsigned int i = 0; i < q; i++) *(v++) = *(x++); } lsLen += q;
		if (z) return; y -= q; send(); lsNo = p_nSite->getStr.get(ls), lsLen = 0; continue;
	} while (true);
}

bool clsNSite::func::closeF() { 
	p_nSite->voegAdr(this); del.store(true); _SOCK_CLOSE_F(*sock); return true; 
}

void clsNSite::func::closeF2() {
	del.store(true); _SOCK_CLOSE_F(*sock);
}
