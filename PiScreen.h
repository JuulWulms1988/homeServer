#pragma once
#include "Telnet.h"
#include "Radio.h"

class piScreenCls;

extern piScreenCls& piScreenC;

class piScreenCls {
public:
	void start();
	mainThreadCls::strMpCha passPrMpCha[102];
	void passPrep(unsigned __int16 s, mainThreadCls::strMpCha& mpCh, unsigned __int8 ad);
	void sluisSend(unsigned __int16 s, unsigned __int16 f);
	void chanF(unsigned __int16 no, unsigned __int8 ad);
	void playF(unsigned __int8 x, unsigned __int8 ad);
	void playPrep(unsigned __int16 x, unsigned __int8 ad);
	bool StreamVidVar(char* x);
	char* chanPoint;
	unsigned __int8 chanCnt = 0;
	bool wakeOnLanF();
	//bool radPlayDel = false;
	struct soundDelayStr {
		mutex mut;
		bool run = false;
		bool set = false;
		bool action[3];
		bool setF(bool* x) {
			bool uit; mut.lock(); uit = !run && (run = true); set = true; for (unsigned __int8 t = 0; t < 3; t++) action[t] = x[t]; mut.unlock(); return uit;
		}
		bool get(bool* x) { bool uit; mut.lock(); if (uit = set && !(set = false)) for (unsigned __int8 t = 0; t < 3; t++) x[t] = action[t]; else run = false; mut.unlock(); return uit; }
	} soundDelayS;


private:
	void playP(unsigned __int8 x, unsigned __int8 ad);
	mutex chanSendMut;
	mainThreadCls::strStrCnt* mpCh;
	friend class ServerTelnet; 
	friend class mainThreadCls::radioStr;
	friend class extCls;
	unsigned __int8 clientCnt;
	mainThreadCls::strMpCh sendMpCh[100];
	struct screenObjS {
		unsigned __int8 adr;
		unsigned __int8 type;
		mainThreadCls::strMpCha sendMpCha;
		SOCKET sock;
		bool connected = false;
		bool stat = false;
		shared_mutex sockConMut;
		char* sBuf;
		mainThreadCls::strMpCh sendMpCh;
		unsigned __int16 sBufLen = 0;
		void set(char* L, unsigned __int8 LL) { if ((type = *L - '0') != 1) adr = (L[1] - '0') * 10 + (L[2] - '0'); else strncpy_s(sBuf, 14, "start vlc.bat", sBufLen = 13); }
		void sendPrep(unsigned __int16 s);
		void send(unsigned __int16 s);
	};
	screenObjS* screenObj;
	char source[512]{ 'd', 'v', 'b', ':', '0', '0', '0', '\0' };
	mutex sourceWmut[100];
	shared_mutex statMut;
	unsigned __int8 statCnt = 0;
	mainThreadCls::strMpCha passMpCha;
	mainThreadCls::strMpCha passMpChaPlay;
	mutex threadMut;
	unsigned __int16 sourceLen = 7;
	unsigned __int8 channel = 0;
	bool chanBl = true;
	bool play = false;
	shared_mutex sourceMut;
	void pass(unsigned __int16 s);
	void func(unsigned __int16 s);
	void soundF(screenObjS& p);
	void serverIO(bool s);
	void statF(bool s, unsigned __int8 a);
	void connectF(unsigned __int8 a);
	char* lsPlay;
	__int8 lsNoPlay;
};

