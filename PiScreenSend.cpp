#include "PiScreen.h"

void piScreenCls::screenObjS::send(unsigned __int16 s) {
	sockConMut.lock_shared();
	if (!connected) { sockConMut.unlock_shared(); return; }
	SOCKET sSock = sock; 
	sockConMut.unlock_shared();
	bool sluiting = false;
	if (s / 512) sluiting = true, strncpy_s(sBuf, 9, "sys OFF\n", sBufLen = 8);
	else if (!(s / 256)) strncpy_s(sBuf, 9, "vlc OFF\n", sBufLen = 8);
	else if (s % 256) { 
		unsigned __int8 chanFFF;
		strncpy_s(sBuf, 8, "vlc ON\n", sBufLen = 7);
		if ([&] { piScreenC.chanSendMut.lock(); piScreenC.sourceMut.lock_shared(); chanFFF = piScreenC.channel; piScreenC.sourceMut.unlock_shared(); piScreenC.chanSendMut.unlock(); return piScreenC.chanBl; }())
			sBuf[3] = chanFFF / 100 + '0', sBuf[4] = (chanFFF / 10) % 10 + '0', sBuf[5] = chanFFF % 10 + '0';
	}
	else strncpy_s(sBuf, 6, "vlc \"", 5), piScreenC.sourceMut.lock_shared(), strncpy_s(sBuf + 5, piScreenC.sourceLen + 1,
		piScreenC.source, piScreenC.sourceLen), sBufLen = piScreenC.sourceLen + 5, piScreenC.sourceMut.unlock_shared(),
		sBuf[sBufLen++] = '\"', sBuf[sBufLen++] = '\n';
	bool uit = true; 
	for (__int8 t = 0; t < 15 && (NetworkServices::sendMessage(sSock, sBuf, sBufLen) == SOCKET_ERROR || (uit = false)); t++);
	if (!uit) 
		if (sluiting) {
			mainThreadCls::trLisHomeCls* x = threadCls->sesPoint(threadCls->sesPMut + adr, threadCls->adresNo(adr));
			if (!x) return;
			char* ls; __int8 lsNo = piScreenC.mpCh->get(ls);
			unsigned __int8 hetNo = this - piScreenC.screenObj; 
			strncpy_s(ls, 4, "@PS", 3);
			ls[3] = adr / 10 + '0'; ls[4] = adr % 10 + '0';
			ls[5] = 'C', ls[6] = 'U';
			ls[7] = strbasprc::cvintcharchar(hetNo / 60);
			ls[8] = strbasprc::cvintcharchar(hetNo % 60);
			ls[9] = '+'; ls[10] = ls[piScreenC.mpCh->len - 2], ls[11] = ls[piScreenC.mpCh->len - 1];
			x->sendPrep(mainThreadCls::strSndV{ ls, -11, NULL, lsNo }, sendMpCh);
			return;
		}
		else return;
	sockConMut.lock();
	if (connected && sSock == sock) closesocket(sSock), connected = false;
	sockConMut.unlock();
}


void piScreenCls::serverIO(bool s) {
	unsigned __int8 ad = screenObj[0].adr;
	mainThreadCls::trLisHomeCls* x = threadCls->sesPoint(threadCls->sesPMut + ad, threadCls->adresNo(ad));
	if (!x) return;
	char* ls; __int8 lsNo = mpCh->get(ls);
	strncpy_s(ls, 4, "@PS", 3); ls[3] = ad / 10 + '0', ls[4] = ad % 10 + '0';
	if (s) ls[5] = 'A', ls[6] = 'N';
	else ls[5] = 'U', ls[6] = 'T';
	ls[7] = ls[8] = '0', ls[9] = '+';
	ls[10] = ls[mpCh->len - 2], ls[11] = ls[mpCh->len - 1];
	x->sendPrep(mainThreadCls::strSndV{ ls, -11, NULL, lsNo }, screenObj[0].sendMpCh);
}

void piScreenCls::soundF(screenObjS& p) {
	bool sound = p.connected, st = p.stat, stA; statMut.lock_shared();
	if (statCnt && screenObj[0].stat) stA = true, statMut.unlock_shared();
	else statMut.unlock_shared(), stA = false; p.sockConMut.unlock_shared();
	bool x[3]{ sound, st, stA };
	if (soundDelayS.setF(x))
		threadBufCls::recStruct{ threadMut, [](void* sBuf, void* N) {
			bool x[3]; //bool& radPlayDel = piScreenC.radPlayDel;
			while (((piScreenCls::soundDelayStr*)N)->get(x)) {
				bool sound = x[0], st = x[1], stA = x[2];
				mainThreadCls::killProc("cmd.exe");
				mainThreadCls::killProc("vlc.exe");
				//if (radPlayDel) Sleep(1000);
				//radPlayDel = false;
				if (!(sound && stA) || (!st && !sound)) continue;
				if (!sound) continue;
				//Sleep(3000);
				system((char*)sBuf);
				//radPlayDel = true;
				//Sleep(1000);
			}
		} }.start(p.sBuf, &soundDelayS);
}