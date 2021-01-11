#include "Telnet.h"

telnetStr& telnetS = *new telnetStr;

void ServerTelnet::update()
{
	while (true) telnetS.lisAccept(network->acceptNewClient());
}

void telnetStr::chkAdVoeg(SOCKET S) {
	chkAdMut.lock();
	if (chkAdCnt < 256) chkAdAr[chkAdCnt++] = chkAdStr{ S, (uint8_t)((p_clstijd->minuut.load() + 1) % 60) };
	else chkAdMp.insert(pair<SOCKET, uint8_t>(S, (p_clstijd->minuut.load() + 1) % 60));
	chkAdMut.unlock();
}

void telnetStr::rmAdArF(SOCKET S) { lock_guard<mutex> lk(chkAdMut); for (uint8_t t = 0; t < chkAdCnt; t++) if (chkAdAr[t].s == S && rmAdAr(t)) return; if (chkAdMp.find(S) != chkAdMp.end()) chkAdMp.erase(S); }

bool ServerTelnet::receiveFromClients(SOCKET S)
{
	char rBuf[4]; uint8_t rBufL = 0;
	do {
		int r; uint8_t t = 0;
		while (true)
			if (_SOCK_RESULT_COMP((r = NetworkServices::receiveMessage(S, rBuf + rBufL, 4 - rBufL))) || !(rBufL += r))
				if (t++ < 14) continue;
				else return false;
			else break;
	} while (rBufL != 4);
		telnetS.rmAdArF(S);
	{
		bool f = false;
		for (char t = 0, w; t < 2; t++) if (!(((w = rBuf[2 + t]) >= 'A' && w <= 'Z') || (w >= '0' && w <= '9') || (w >= 'a' && w <= 'x')) && (f = true)) break;
		if (f) {
			_SOCK_CLOSE_F(S); return true;
		}
	}
	switch (rBuf[0]) {
	case 'P': switch (rBuf[1]) { case 'S': accept_piScreen(strbasprc::cvintcharint(rBuf[2]) * 60 + strbasprc::cvintcharint(rBuf[3]), S);  }
	}
	_SOCK_CLOSE_F(S);
		return true;
}

void telnetStr::checkAdr(uint8_t min) {
	if (!min) min = 59; else min--;
	chkAdMut.lock();
	uint8_t w;
	for (int t = 0; t < chkAdCnt; t++) if ((w = chkAdAr[t].min) <= min || w > min + 2) _SOCK_CLOSE_F(chkAdAr[t].s), rmAdAr(t--);
	bool del = false;
	map<SOCKET, uint8_t>::iterator t, d;
	for (t = chkAdMp.begin(), d; t != chkAdMp.end(); t++) {
		if (del) del = false, chkAdMp.erase(d);
		if ((w = t->second) <= min || w > min + 2) del = true, d = t, _SOCK_CLOSE_F(t->first);
	} if (del) chkAdMp.erase(d);
	chkAdMut.unlock();
}

void mainThreadCls::exMesOne::chckTelAd() {
	telnetS.checkAdr(p_clstijd->minuut.load());
}