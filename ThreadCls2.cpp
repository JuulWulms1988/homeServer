#include "ThreadCls.h"
#include "Radio.h"
#include <thread>
#include "clstijd.h"
#include "Statvars.h"
#include <sstream>
#include "Custom/custom_string.h"
#include "udpImplementation/Implementation.hpp"

#ifdef _WIN32
#include <process.h>
#include <Tlhelp32.h>
#include "../stdafx.h"
#endif

#ifndef _WIN32
#include <stdio.h>
#endif


unsigned int balans = 0;
bool kaasdel = false;


mainThreadCls::clsExMes::clsExMes(trLisHomeCls* pp) {
	{
		pLisHome = pp;
		
		for (int8_t t = 0, z = 99; t < 99; t++) lsA[t] = z--;

		
		for (int8_t t = 0; t < 20; t++) exCls.set(t, t);
		char* jj;
		{ int8_t t = 1; strExec* y = exCls.i; while ((t - 1 && t < 21 && y++) || t == 1) y->set(this, getStr(jj)), t++; }
	}
	cvEx.ready = true;
}

char* charPrint(unsigned int x, string& a) {
	return NULL;
	stringstream strs;
	strs << x;
	a = strs.str();
	return (char*)a.c_str();
}


mainThreadCls::strMpCh printMap;



void printTijdel(char** p, unsigned int l) {
	return;
	char** pp = new char*[l];
	char * aa = new char[32];
	aa[strbasprc::cvcharlngth(60, (unsigned long) pp, aa)] = '\0';
	for (unsigned int t = 0; t < l; t++) {
		unsigned int ll = strbasprc::charPLen(p[t]);
		pp[t] = new char[ll + 1]; strncpy_s(pp[t], ll + 1, p[t], ll);
	}

	if (!printMap.begin(mainThreadCls::strSndV{ aa, (int)l })) return;
	thread ([]() {
		do {
			int L = printMap.p.len; char ** PP = (char**)strbasprc::cvintcharStr(printMap.p.pack); delete[] printMap.p.pack;
			for (unsigned int T = 0; T < L; T++)
				cout << PP[T];
			for (unsigned int T = 0; T < L; T++) delete[] PP[T];
			cout << "\n";
			delete[] PP;
		} while (!printMap.end());
	}).detach();
}

extern clstijd* p_clstijd;
extern statvars* p_statvars;

void mainThreadCls::voegAdr(uint8_t sess) {
	lock_guard<mutex> lk(mutChkAd);
	if (mpChkAd.find(sess) != mpChkAd.end()) mpChkAd.erase(sess);
}

void mainThreadCls::checkAdr(uint8_t min) {
	if (min < 2) min = 60 - (2 - min); else min -= 2;
	blArdChk[0] = blArdChk[1] = 0; uint8_t y;
	lock_guard<mutex> lk(mutChkAd);
	{
		bool dell = false; uint8_t aa;
		for (map<uint8_t, int8_t>::iterator it = mpChkAd.begin(); it != mpChkAd.end(); it++)
		{
			if (dell) dell = false, mpChkAd.erase(aa);
			if ((blArdChk[0] = true, y = it->second) <= min || y > min + 2)
				ses.find(it->first)->second->closeF(), dell = true, aa = it->first, blArdChk[1] = true;
		} if (dell) mpChkAd.erase(aa);
	}
	if (blArdChk[0] == blArdChk[1]) blmutChkAd.store(false);
}

void mainThreadCls::clsExMes::strExec::cancel() { 
	if (lsNow == 100) delete[] ls; else point->retStr(lsNow); 
}

mainThreadCls::clsExMes::~clsExMes() {
	exCls.wait(); unique_lock<mutex>lk(sendMut); cvSend.wait(lk, [&] { return lsT / 100; });
}


mainThreadCls::trLisHomeCls* mainThreadCls::sesPoint(mutex* mut, uint8_t no) {
	if (no == 255) return NULL;
	mut->lock();
	shared_lock<shared_mutex> lk(threadCls->sMutSes);
	map<uint8_t, trLisHomeCls*>::iterator it; if ((it = ses.find(no)) != ses.end()) { mut->unlock(); return it->second; } mut->unlock(); return NULL;
}

uint8_t mainThreadCls::adresNo(uint8_t no) { shared_lock<shared_mutex> lk(sMutAdr); return adress[no]; }

void mainThreadCls::trAcc(SOCKET* s)
{
	{ lock_guard<mutex> lk(mutChkAd); mpChkAd.insert(pair<uint8_t, int8_t>(accHome->mpSesNo.load(), p_clstijd->minuut.load())); blmutChkAd.store(true); }
	{ thread t([](trLisHomeCls* x, SOCKET s) { x->loop(&s); }, accHome, *s); t.detach(); }
	accHome = new trLisHomeCls(); if (newSes()) { { unique_lock<mutex> lk(cvAcc.mut); cvAcc.ready = true; } cvAcc.cv.notify_one(); return; }
	{ unique_lock<mutex>(cvAcc.mut); cvAcc.ready = true; sesFull = true; } cvAcc.cv.notify_one();
	{ unique_lock<mutex> lk(cvAccFull.mut); cvAccFull.ready = true;
	cvAccFull.cv.wait(lk, [&] {return !cvAccFull.ready; }); } newSes();
	{ unique_lock<mutex> lk(cvAcc.mut); sesFull = false; }
}


bool mainThreadCls::newSes() {
	{ unique_lock<shared_mutex> lk(sMutSes);
	for (uint8_t t = 0; t < 255; t++) if (ses.find(t) == ses.end())
	{ ses.insert(pair<uint8_t, trLisHomeCls*>(accHome->mpSesNo = t, accHome)); return true; } } return false; 
}

//extern mutex ffMut;

void mainThreadCls::trLisHomeCls::messPr(char* mes, unsigned int len)
{
	// 0 = adrs stat 1 = statverzlees 2 = lezen
	for (unsigned int t = 0; t < len; t++)
		if ((thisChar = mes[t]) == '|') strLen = strAanv = 0;
		else if (strAanv)
			if (thisChar == '+') //{
				//{
				//	mesStr[strLen] = '\0'; ffMut.lock(); cout << "Lees(" << (int)adrs.load() << "): " << mesStr << '\n'; ffMut.unlock();
				//}
				if (strAanv != 1) { 
					if (!timedMesF(strSndV{ mesStr, (int)strLen, exMes, exNow }))exCls->voeg(clsExMes::var{ mesStr, exNow, (uint8_t)strLen, (int8_t)(strAanv - 2) }); exNow = exMes->getStr(mesStr), strLen = strAanv = 0;
				}
				else {
					for (int8_t t = 0; t < 3; t++) if (t < 2) if (mesStr[t] < '0' || mesStr[t] > '9') break; else continue;
					else if (adrs.load() == 255)
					{
						threadCls->voegAdr(mpSesNo.load());
						adAd = ((mesStr[0] - '0') * 10) + (mesStr[1] - '0'); threadCls->sMutAdr.lock();
						if ((strAanv = threadCls->adress[adAd]) != 255) NetworkMethods::sockCloseF(threadCls->ses.find(strAanv)->second->socket);
						threadCls->adress[adAd] = mpSesNo.load();
						adrs.store(adAd);
						timedComNo = threadCls->timedComNoS[adAd].set();
						//string sfs; char*c[]{ "VoegAdr: ", charPrint(unsigned int(adAd), sfs) }; printTijdel(c, 2);
						threadCls->sMutAdr.unlock();
					}
					strLen = strAanv = 0; continue;
				}
			//}
			else mesStr[strLen++] = thisChar;
		else for (uint8_t tt = 0; tt < 3; tt++) if (thisChar == aanv[tt]) strAanv = tt + 1;
}

void mainThreadCls::tijdProc() {
	(new exMesOne)->tijdPr();
}

void mainThreadCls::clsExMes::strExec::main() {
	switch (str[0]) {
	case 'S': switch (str[1]) { case 'D': if (!passMes()) strNow = point->getStr(str); return; case 'P': voegLedPlaf(point->pLisHome->adrs.load()); break; } break;
	//case 'V': switch (str[1]) { case 'R': radio(true); return; case 'r': radio(false); return; } break;
	case 'T': switch (str[1]) { case 'E': temp(); return; } break;
	case 'D': switch (str[1]) { case 'B': {str[len] = '\0'; char p[]{'D', 'e', 'b', 'u', 'g', 'b', 'e', 'r', 'i', 'c', 'h', 't', ':', ' '}, *c[]{ p, str + 2 }; printTijdel(c, 2); } return; case 'M': return; } break;
	case 'P': switch (str[1]) { case 'S': piScreenF(); return; } break;
	}
	readMes();
}

void mainThreadCls::clsExMes::strExec::temp() {
	statvars::strtemp& p = *p_statvars->mptemp.find(strbasprc::cvintcharint(str[2]))->second;
	p.temp.store(strbasprc::cvintcharint(str[3]) - 20); buf[0] = '@'; strncpy_s(buf + 1, 5, str, 4); buf[5] = '+';
	for (uint8_t t = 0, y = 0; (y = p.client[t]) != 255; t++) { zendId = threadCls->adresNo(strAd = y); strncpy_s(ls, 7, buf, 6); sendLen = 6; send(true); }
}

void mainThreadCls::killProc(const char* x) {
#ifdef _WIN32
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
	PROCESSENTRY32 pEntry;
	pEntry.dwSize = sizeof(pEntry);
	BOOL hRes = Process32First(hSnapShot, &pEntry);
	while (hRes)
	{
		if (strcmp(pEntry.szExeFile, x) == 0)
		{
			HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0, (DWORD)pEntry.th32ProcessID);
			if (hProcess) TerminateProcess(hProcess, 9), CloseHandle(hProcess);
		}
		hRes = Process32Next(hSnapShot, &pEntry);
	}
	CloseHandle(hSnapShot);
#endif

#ifndef _WIN32
	char y[256]{ 's', 'u', 'd', 'o', ' ', 'k', 'i', 'l', 'l', 'a', 'l', 'l', ' ' }, z[]{ '%', 's', '\0' };
	system((sprintf(y + 13, z, x), y));
#endif
}

void mainThreadCls::clsExMes::strExec::send(bool x) {
	uint8_t ad2 = point->pLisHome->adrs.load();
	if (!x && sendLen > 11 && ls[1] == 'U' && ls[2] == 'V') {
		if (bufXX = threadCls->sesPoint(threadCls->sesPMut + ad2, zendId)) naCheckF(strSndV{ ls, sendLen, point, lsNow }, strAd, ad2);
		else naCheckF(strSndV{ ls, sendLen, point, lsNow }, ad2, ad2);
		lsNow = point->getStr(ls);
	}
	else if (bufXX = threadCls->sesPoint(threadCls->sesPMut + ad2, zendId)) bufXX->sendPrep({ ls, sendLen, point, lsNow }, threadCls->mpChS[ad2][strAd]), lsNow = point->getStr(ls);
	sendLen = 0;
}



int8_t mainThreadCls::clsExMes::getStr(char*& x) {
	{
		unique_lock<mutex> lk(sendMut);
		if (lsT) { int8_t y; x = lsP + ((y = lsA[--lsT]) * 32); 
		return y; }
	} x = new char[32]; return 100;
}

void mainThreadCls::exMesOne::tijdUpdate() {
	if (p_clstijd->tijdupdate()) {
		{
			lock_guard<mutex> lk(threadCls->timeMut);
			if (p_clstijd->timeUpdC)
				for (uint8_t t = 0, *p = p_clstijd->timeUpd, &m = p_clstijd->timeUpdC; t < m || (m = 0); t++)
					lsNow = udpImplementation::stringPool->get(ls), tijdUpdate2('T', p[t]);
		}
		if (p_clstijd->seconde >= 30 && p_clstijd->seconde < 45 && p_clstijd->minuut != p_clstijd->minuutgestuurd) {
			p_clstijd->minuutgestuurd = p_clstijd->minuut;
			lsNow = udpImplementation::stringPool->get(ls);
			tijdUpdate2('U', 255);
			if (threadCls->blmutChkAd.load()) threadCls->checkAdr(p_clstijd->minuut);
			chckSiteAd(), chckTelAd();
		}
	}
}

void mainThreadCls::exMesOne::tijdPr() {
	thread([&] { while (true) tijdUpdate(),
#ifdef _WIN32
		Sleep(10); 
#endif
#ifndef _WIN32
		usleep(10);
#endif
		}).detach();
}

void mainThreadCls::exMesOne::tijdUpdate2(char update, uint8_t adress) {
	sendLen = 3;
	ls[1] = 'T'; ls[2] = update;
	ls[0] = '@' + p_clstijd->timer[0];
	switch (p_clstijd->kwart) {
	case 0:
		ls[1] += 32;
		ls[2] += 32;
		break;
	case 1:
		ls[1] += 32;
		break;
	case 2:
		ls[2] += 32;
		break;
	}
	switch (update) {
	case 'U':
		while (sendLen < 6) ls[sendLen++] = strbasprc::cvintcharchar(p_clstijd->stuur(sendLen));
		break;
	case 'T':
		while (sendLen < 9) ls[sendLen++] = strbasprc::cvintcharchar(p_clstijd->stuurt(sendLen));
		sendLen += strbasprc::cvcharlngth(60, p_clstijd->jaar, &ls[sendLen]);
		break;
	}
	ls[sendLen++] = '+'; ls[sendLen] = '\0';
	if (adress == 255) ls[sendLen - 1] = '\0',	udpImplementation::sendPrep(strSndV{ udpImplementation::stringPool->lPosF(ls, sendLen), sendLen, NULL, lsNow });
	else zendId = threadCls->adresNo(strAd = adress), send();
}

void mainThreadCls::exMesOne::send() {
	if (!(bufX = threadCls->sesPoint(threadCls->sesPMut + zendId, zendId))) { udpImplementation::stringPool->ret(lsNow); return; }
	strSndV s{ udpImplementation::stringPool->lPosF(ls, sendLen), sendLen * (-1) - 1 , NULL, lsNow }; 
	bufX->send(s, 0);
}

void mainThreadCls::clsExMes::strExec::stReq() {
	strncpy_s(buf, 17, "Statusverzoeken/", 16); strncpy_s(buf + 16, 5, str, 4); strncpy_s(buf + 20, 5, ".txt", 4);
	if (!fileObj.open(buf)) { return; }
	uint8_t theAd = point->pLisHome->adrs.load();
	{
		uint8_t radAr[255], radCnt = 0;
		uint8_t psBl;
		while (!strbasprc::vergCharP(strbasprc::remCommCharP(strbasprc::charPLsR(buf, fileObj.file, fileObj.loc)), "EE")) {
			strAd = ((buf[2] - '0') * 10) + (buf[3] - '0');
			if (buf[0] == 'T' && (buf[1] == 'T' || buf[1] == 'E'))
				if (buf[1] == 'T') {
					lock_guard<mutex> lk(threadCls->timeMut);
					for (uint8_t t = 0, &m = p_clstijd->timeUpdC, *p = p_clstijd->timeUpd; t < m || (p[m++] = strAd, 0); t++)
						if (p[t] == strAd) break;
					/*
					for (unsigned int t = 1; t > 0; t++)
						if (tijdsv.find(t - 1) == tijdsv.end()) {
							tijdsv.insert(pair<unsigned int, uint8_t>(t - 1, strAd)); break;
						}
						*/
				}
				else {
					int8_t temp = p_statvars->mptemp.find(strbasprc::cvintcharint(buf[4]))->second->temp.load();
					if (temp == 40) continue;
					strncpy_s(ls, 4, "@TE", 3); ls[3] = buf[4]; ls[4] = strbasprc::cvintcharchar(temp + 20); ls[5] = '+'; sendLen = 6;
					zendId = threadCls->adresNo(strAd); send(true);
				}
			else if (buf[0] == 'K' && buf[1] == 'C') {
				strncpy_s(ls, 4, "@KC", 3); ls[3] = buf[4]; ls[4] = '+'; sendLen = 5;
				zendId = threadCls->adresNo(strAd); send(true);
			}
			else if (buf[0] == 'P' && buf[1] == 'S') {
				sluisPiScreenF(768, (buf[2] - '0') / 10 + (buf[3] - '0') % 10);
			}
			else {
				blDim = stverzDim(); ls[0] = '@'; sendLen = strbasprc::charPVCI(ls, buf, 1); ls[sendLen++] = '+';
				strncpy_s(buf, 11, "Apparaten/11/Nummers/", 10); buf[10] = ls[3]; buf[11] = ls[4];
				strncpy_s(buf + 12, 15, "/Statusgevers/", 14);
				strncpy_s(buf + 26, sendLen - 1, ls + 1, sendLen - 2); {
					uint8_t bL = sendLen - 2 + 26; strncpy_s(buf + bL, 5, ".txt", 4); buf[bL + 4] = '\0';
				}
				fLock();
				if (!fileObj.open(buf)) { fUnlock(); continue; }
				if ([&](char* bUf) {
					if (bUf[0] != 'V' || bUf[1] != 'R') return false;
						for (uint8_t t = (bUf[2] - '0') * 100 + (bUf[3] - '0') * 10 + (bUf[4] - '0'), T = 0; T < radCnt || (!(bUf = NULL) && (radAr[radCnt++] = t) && false); T++)
							if (radAr[T] == t) break;
						if (!bUf) radioS.pass(theAd + radAr[radCnt - 1] * 256, theAd);
						fUnlock(); return true;
				}(fileObj.file)) continue;
				if ([&](char* bUf) {
					if (bUf[0] != 'P' || bUf[1] != 'S') return false;
					if (!psBl) psBl = true, psPlayF(0, theAd);
					fUnlock(); return true;
				}(fileObj.file)) continue;
				if (!strbasprc::vergCharP(fileObj.file, "GG")) {
					strncpy_s(buf2, 11, "Apparaten/11/Nummers/", 10); char ad2[2] = { buf2[10] = fileObj.file[0], buf2[11] = fileObj.file[1] };
					strncpy_s(buf2 + 12, 10, "/Nummers/", 9); {
						bufX = strbasprc::charPLen(fileObj.file); strncpy_s(buf2 + 21, bufX + 1, fileObj.file, bufX);
						strncpy_s(buf2 + (bufX += 21), 5, ".txt", 4); buf2[bufX + 4] = '\0'; } if (!fileObj.open(buf2)) { fUnlock(); continue; } strbasprc::charPLsR(buf, fileObj.file, fileObj.loc);
						{
							int nuo = (buf[0] - '1') * 100 + (buf[1] - '0') * 10 + (buf[2] - '0');
							ls[5] = strbasprc::cvintcharchar(nuo / 60), ls[6] = strbasprc::cvintcharchar(nuo % 60); if (blDim) ls[1] += 32;
						}
						ls[sendLen] = ad2[0], ls[sendLen + 1] = ad2[1];
						naCheckF(strSndV{ ls, sendLen, point, lsNow }, theAd, theAd), lsNow = point->getStr(ls), sendLen = 0;
				}
				fUnlock();
			}
		}
	}
	if (len != 5 || str[4] != 'R') { return; }
		while (!strbasprc::vergCharP(strbasprc::remCommCharP(strbasprc::charPLsR(buf, fileObj.file, fileObj.loc)), "GG")) {
		strAd = ((buf[0] - '0') * 10) + (buf[1] - '0'); blDim = stverzDim(); sendLen = strbasprc::charPLen(buf);
		strncpy_s(ls, 4, "@UV", 3); strncpy_s(ls + 3, sendLen + 1, buf, sendLen); ls[(sendLen += 3)++] = '+';
		strncpy_s(buf2, 11, "Apparaten/11/Nummers/", 10); buf2[10] = buf[0]; buf2[11] = buf[1]; strncpy_s(buf2 + 12, 10, "/Nummers/", 9);
		strncpy_s(buf2 + 21, sendLen - 3, buf, sendLen - 4); strncpy_s(buf2 + 21 + (sendLen - 4), 5, ".txt", 4);
		fLock();
		if (!fileObj.open(buf2)) { fUnlock(); continue; } strbasprc::charPLsR(buf, fileObj.file, fileObj.loc);
		
		{
			int nuo = (buf[0] - '1') * 100 + (buf[1] - '0') * 10 + (buf[2] - '0');
			ls[5] = strbasprc::cvintcharchar(nuo / 60), ls[6] = strbasprc::cvintcharchar(nuo % 60); if (!blDim) ls[1] = 'u'; else ls[1] = 'd';
		}
		uint8_t adT = point->pLisHome->adrs.load();
		naCheckF(strSndV{ ls, sendLen, point, lsNow }, adT, adT), lsNow = point->getStr(ls), sendLen = 0;
		fUnlock();
	}
}

void mainThreadCls::clsExMes::strExec::readMes() {
	strncpy_s(buf, 11, "Apparaten/11/Nummers/", 10); buf[10] = str[2]; buf[11] = str[3]; strncpy_s(buf + 12, 11, "/Signalen/", 10); strncpy_s(buf + 22, len - 1, str + 2, len - 2); strncpy_s(buf + len + 20, 5, ".txt", 4);
	if (!fileObj.open(buf) || strbasprc::vergCharP(fileObj.file, "GG")) { return; } len = strbasprc::charPLen(fileObj.file); strncpy_s(str, len + 1, fileObj.file, len);
	actionFunc();
}

void mainThreadCls::clsExMes::strExec::actionWFunc() {
	strAd = (*str - '0') * 10 + (str[1] - '0');
	strncpy_s(ls, 4, "@UV", 3); sendLen = len + 3; strncpy_s(ls + 3, len + 1, str, len); ls[sendLen++] = '+';
	zendId = threadCls->adresNo(strAd); send(false);
}

void mainThreadCls::clsExMes::strExec::actionFunc() {
	strncpy_s(buf, 9, "Actions/Namen", 8); strncpy_s(buf + 8, len + 1, str, len); strncpy_s(buf + 8 + len, 5, ".txt", 4);
	if (!fileObj.open(buf)) return;
	while (!strbasprc::vergCharP(strbasprc::remCommCharP(strbasprc::charPLsR(buf, fileObj.file, fileObj.loc)), "GG")) 
		if (buf[0] == 'N' && buf[1] == 'A') {
			bufX = strbasprc::charPLen(buf) - 2;
			zendId = point->getStr(file);
			strncpy_s(file, bufX + 1, buf + 2, bufX);
			pExMp->voeg(var{ file, (int8_t)zendId, bufX, -2 });
		}
		else {
			if (buf[0] == 'V' && buf[1] == 'R') { radioS.pass((103 - buf[5] / 'U') + ((buf[2] - '0') * 100 + (buf[3] - '0') * 10 + (buf[4] - '0')) * 256, point->pLisHome->adrs.load()); continue; }
			if (buf[0] == 'P' && buf[1] == 's') { psPlayF(2 - buf[2] / 'U', point->pLisHome->adrs.load()); continue; }
			strAd = (buf[2] - '0') * 10 + (buf[3] - '0');
			if (buf[0] == 'S' && buf[1] == 'P') { passLpFromC(); continue; }
			if (buf[0] == 'P' && buf[1] == 'S') { sluisPiScreenFC(); continue; }
			ls[0] = '@'; sendLen = strbasprc::charPLen(buf) + 1; strncpy_s(ls + 1, sendLen, buf, sendLen - 1); ls[sendLen++] = '+';
			zendId = threadCls->adresNo(strAd); bufX = sendLen - 2; send(false);
		}
}

bool mainThreadCls::clsExMes::strExec::passMes() {
	uint8_t s_val = 0, s_type = 0; unsigned int s_no; strSndV s_s;
	if (len < 0) {
		len = (len + 1) * (-1);
		if (str[1] == 'u') str[0] = 's', s_type = 2; else if (str[1] == 'd') str[0] = 'd', s_type = 3; str[1] = 'D'; len -= 2;
		for (int t = 2; t < len; t++) str[t] = str[t + 1];
		s_no = strbasprc::cvintcharint(str[4]) * 60 + strbasprc::cvintcharint(str[5]); s_s = strSndV{ str, len, point, strNow };
	}	
	else if (str[1] == 'U' && str[2] == 'V') {
		strncpy_s(buf, 11, "Apparaten/11/Nummers/", 10); buf[10] = str[3]; buf[11] = str[4]; strncpy_s(buf + 12, 10, "/Nummers/", 9); strncpy_s(buf + 21, len - 3, str + 3, len - 4); strncpy_s(buf + 17 + len, 5, ".txt", 4); buf[23] = 'N'; buf[24] = 'O';
		if (!fileObj.open(buf)) { return true; } strbasprc::remCommCharP(strbasprc::charPLsR(buf, fileObj.file, fileObj.loc));
		s_no = (buf[0] - '1') * 100 + (buf[1] - '0') * 10 + (buf[2] - '0'); if (sStrBuf) s_s = *sStrBuf; else s_s = strSndV{ str, len, point, strNow };
		if ((str[5] == 'A' && str[6] == 'N' && (s_val = 1)) || (str[5] == 'U' && str[6] == 'T' && !(s_val = 0))) s_type = 0;
		else if (((str[5] >= '0' && str[5] <= '9') || (str[5] >= 'a' && str[5] <= 'f')) && ((str[6] >= '0' && str[6] <= '9') || (str[6] >= 'a' && str[6] <= 'f'))) s_type = 1, s_val = strbasprc::cv16waarde(str + 5);
		else return true;
	} 
	else {
	if (str[1] < 97) s_type = 4; else s_type = 5, str[1] -= 32;
	s_no = strbasprc::cvintcharint(str[5]) * 60 + strbasprc::cvintcharint(str[6]); s_s = strSndV{ str, len, point, strNow };
	}

threadCls->statStruc[(s_type % 2) * 900 + s_no].start(stSndStt{ s_type, s_no, s_val, fileObj.loc, point, fileObj.file, s_s }, point->pLisHome->adrs.load()); return false;
}

bool mainThreadCls::clsExMes::strExec::stverzDim() {
	if (buf[3] == 'D') buf[3] = 'O'; 
	else if (buf[5] == 'D') buf[5] = 'O';
	else return false;
	return true;
}

void mainThreadCls::clsExMes::strExec::passLpFromC() {
		ls[sendLen++] = 'P'; 
		ls[(sendLen += strbasprc::cvcharlngth(60, getPointLed(fileObj.file + fileObj.loc), ls + 1))] = '\0';
		sendLedPl(point->pLisHome->adrs.load());
		strbasprc::charPLsR(buf, fileObj.file, fileObj.loc);
}