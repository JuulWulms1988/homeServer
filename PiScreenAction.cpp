#include "PiScreen.h"

void piScreenCls::connectF(unsigned __int8 a) {
	screenObjS* p = &screenObj[a];
	p->sockConMut.lock_shared();
	if (((a && !p->type) || !a) && !p->connected) { 
		p->sockConMut.unlock_shared(); return; 
	} 
	if (a && p->type == 1) soundF(*p);
	else {
		p->sockConMut.unlock_shared();
		bool ssS; statMut.lock_shared(), ssS = screenObj[0].stat, statMut.unlock_shared();
		p->sendPrep(a + (ssS && [&] { bool UuU; screenObj[0].sockConMut.lock_shared(); UuU = screenObj[0].connected; screenObj[0].sockConMut.unlock_shared(); return UuU; }()) * 256);
		if (!a) {
			for (unsigned __int8 t = 1, m = clientCnt + 1; t < m; t++) {
				(p = &screenObj[t])->sockConMut.lock_shared();
				if (p->type == 1 && (p->connected || p->stat)) soundF(*p);
				else if (p->type != 1 && p->connected) p->sendPrep(t + (ssS * 1) * 256), p->sockConMut.unlock_shared();
				else p->sockConMut.unlock_shared();
			}
		}
	}
}

void piScreenCls::statF(bool s, unsigned __int8 a) {
	screenObjS* p = &screenObj[a];
	p->sockConMut.lock();
	if (p->stat != s) {
		statMut.lock();
		p->stat = s;
		bool niet = true; if (p->type == 1 && p->connected && statCnt && screenObj[0].stat && (s || (!s && statCnt > 1))) niet = false;
		if (a && ((s && !statCnt++) || (!s && !--statCnt))) {
			statMut.unlock(), p->sockConMut.unlock();
			serverIO(s);
			for (unsigned __int8 t = 1, m = clientCnt + 1; t < m; t++) 
				if (screenObj[t].type == 1 && t != a) {
					screenObjS& P = screenObj[t];
					P.sockConMut.lock_shared();
					if (P.connected) soundF(screenObj[t]);
					else P.sockConMut.unlock_shared();
					break;
				}
		}
		else statMut.unlock(), p->sockConMut.unlock();
		if (niet) connectF(a);
	}
	else p->sockConMut.unlock();
}

void mainThreadCls::piScreenOffSluis(unsigned __int16 ad) {
	piScreenC.sluisSend(512 + ad, ad);
}

void piScreenCls::sluisSend(unsigned __int16 s, unsigned __int16 f) {
	screenObj[f].sendPrep(s);
}

void piScreenCls::screenObjS::sendPrep(unsigned __int16 s) {
	if (!sendMpCha.begin(s)) return;
	threadBufCls::recStruct{ telnetS.tMut, [](void* pMCh, void* p) {
		do ((screenObjS*)p)->send(((mainThreadCls::strMpCha*)pMCh)->p); while (!((mainThreadCls::strMpCha*)pMCh)->end());
	} }.start(&sendMpCha, this);
}

void mainThreadCls::radioStr::connSoundPiF(bool x) {
	piScreenCls::screenObjS* p = piScreenC.screenObj;
	{
		bool uit = true;
		unsigned __int8 t = 0, m = piScreenC.clientCnt;
		while (t++ < m && ((++p)->type != 1 || (uit = false)));
		if (uit) return;
	}
	p->sockConMut.lock(), p->connected = x, p->sockConMut.unlock(); 
	piScreenC.passPrep(p - piScreenC.screenObj, piScreenC.passPrMpCha[100], 100);
}

bool piScreenCls::wakeOnLanF() {
	bool x; 
	screenObj[0].sockConMut.lock_shared(); 
	x = screenObj[0].connected; 
	screenObj[0].sockConMut.unlock_shared(); 
	return x;
}

void mainThreadCls::clsExMes::strExec::piScreenF() {
	if (str[4] == 'A' && str[5] == 'N') {
		system("wolcmd 001b38d54f0d 192.168.180.30 255.255.255.0");
		if (!piScreenC.wakeOnLanF()) return;
		unsigned __int8 ad = point->pLisHome->adrs.load();
		if (ad == 255) return;
		strncpy_s(ls, 4, "@PS", 3), ls[3] = ad / 10 + '0', ls[4] = ad % 10 + '0';
		strncpy_s(ls + 5, 6, "CA00+", 5);
		point->pLisHome->sendPrep(strSndV{ ls, -11, point, lsNow }, threadCls->mpChS[ad][ad]);
		lsNow = point->getStr(ls);
	}
	else if (str[4] == 'U' && str[5] == 'T') {
		piScreenOffSluis(strbasprc::cvintcharint(str[2]) * 60 + strbasprc::cvintcharint(str[3]));
	}
}