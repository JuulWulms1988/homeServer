#include "Telnet.h"

telnetStr& telnetS = *new telnetStr;

void ServerTelnet::update()
{
	while (true) telnetS.lisAccept(network->acceptNewClient());
}

void telnetStr::chkAdVoeg(SOCKET S) {
	chkAdMut.lock();
	if (chkAdCnt < 256) chkAdAr[chkAdCnt++] = chkAdStr{ S, (unsigned __int8)((p_clstijd->minuut.load() + 1) % 60) };
	else chkAdMp.insert(pair<SOCKET, unsigned __int8>(S, (p_clstijd->minuut.load() + 1) % 60));
	chkAdMut.unlock();
}

void telnetStr::rmAdArF(SOCKET S) { lock_guard<mutex> lk(chkAdMut); for (unsigned __int8 t = 0; t < chkAdCnt; t++) if (chkAdAr[t].s == S && rmAdAr(t)) return; if (chkAdMp.find(S) != chkAdMp.end()) chkAdMp.erase(S); }

bool ServerTelnet::receiveFromClients(SOCKET S)
{
	char rBuf[4]; unsigned __int8 rBufL = 0;
	do {
		int r; unsigned __int8 t = 0;
		while (true)
			if ((r = NetworkServices::receiveMessage(S, rBuf + rBufL, 4 - rBufL)) <= 0 || !(rBufL += r))
				if (t++ < 14) continue;
				else return false;
			else break;
	} while (rBufL != 4);
		telnetS.rmAdArF(S);
	{
		bool f = false;
		for (char t = 0, w; t < 2; t++) if (!(((w = rBuf[2 + t]) >= 'A' && w <= 'Z') || (w >= '0' && w <= '9') || (w >= 'a' && w <= 'x')) && (f = true)) break;
		if (f) {
			closesocket(S); return true;
		}
	}
	switch (rBuf[0]) {
	case 'P': switch (rBuf[1]) { case 'S': accept_piScreen(strbasprc::cvintcharint(rBuf[2]) * 60 + strbasprc::cvintcharint(rBuf[3]), S);  }
	}
	closesocket(S);
		return true;
}

void telnetStr::checkAdr(unsigned __int8 min) {
	if (!min) min = 59; else min--;
	chkAdMut.lock();
	unsigned __int8 w;
	for (int t = 0; t < chkAdCnt; t++) if ((w = chkAdAr[t].min) <= min || w > min + 2) closesocket(chkAdAr[t].s), rmAdAr(t--);
	bool del = false;
	map<SOCKET, unsigned __int8>::iterator t, d;
	for (t = chkAdMp.begin(), d; t != chkAdMp.end(); t++) {
		if (del) del = false, chkAdMp.erase(d);
		if ((w = t->second) <= min || w > min + 2) del = true, d = t, closesocket(t->first);
	} if (del) chkAdMp.erase(d);
	chkAdMut.unlock();
}

void mainThreadCls::exMesOne::chckTelAd() {
	telnetS.checkAdr(p_clstijd->minuut.load());
}