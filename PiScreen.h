#pragma once
#include "Telnet.h"
#include "Radio.h"

class piScreenCls;

extern piScreenCls& piScreenC;

class piScreenCls {
public:
	void start();
	mainThreadCls::strMpCha passPrMpCha[102];
	void passPrep(uint16_t s, mainThreadCls::strMpCha& mpCh, uint8_t ad);
	void sluisSend(uint16_t s, uint16_t f);
	void chanF(uint16_t no, uint8_t ad);
	void playF(uint8_t x, uint8_t ad);
	void playPrep(uint16_t x, uint8_t ad);
	bool StreamVidVar(char* x);
	char* chanPoint;
	uint8_t chanCnt = 0;
	bool wakeOnLanF();
	//bool radPlayDel = false;
	struct soundDelayStr {
		mutex mut;
		bool run = false;
		bool set = false;
		bool action[3];
		bool setF(bool* x) {
			bool uit; mut.lock(); uit = !run && (run = true); set = true; for (uint8_t t = 0; t < 3; t++) action[t] = x[t]; mut.unlock(); return uit;
		}
		bool get(bool* x) { bool uit; mut.lock(); if (uit = set && !(set = false)) for (uint8_t t = 0; t < 3; t++) x[t] = action[t]; else run = false; mut.unlock(); return uit; }
	} soundDelayS;


private:
	void playP(uint8_t x, uint8_t ad);
	mutex chanSendMut;
	mainThreadCls::strStrCnt* mpCh;
	friend class ServerTelnet; 
	friend class mainThreadCls::radioStr;
	friend class extCls;
	uint8_t clientCnt;
	mainThreadCls::strMpCh sendMpCh[100];
	struct screenObjS {
		uint8_t adr;
		uint8_t type;
		mainThreadCls::strMpCha sendMpCha;
		SOCKET sock;
		bool connected = false;
		bool stat = false;
		shared_mutex sockConMut;
		char* sBuf;
		mainThreadCls::strMpCh sendMpCh;
		uint16_t sBufLen = 0;
		void set(char* L, uint8_t LL) { if ((type = *L - '0') != 1) adr = (L[1] - '0') * 10 + (L[2] - '0'); else { char p[]{ 's', 't', 'a', 'r', 't', ' ', 'v', 'l', 'c', '.', 'b', 'a', 't', '\0' }; memcpy(sBuf, p, 14); sBufLen = 13; } }
		void sendPrep(uint16_t s);
		void send(uint16_t s);
	};
	screenObjS* screenObj;
	char source[512]{ 'd', 'v', 'b', ':', '0', '0', '0', '\0' };
	mutex sourceWmut[100];
	shared_mutex statMut;
	uint8_t statCnt = 0;
	mainThreadCls::strMpCha passMpCha;
	mainThreadCls::strMpCha passMpChaPlay;
	mutex threadMut;
	uint16_t sourceLen = 7;
	uint8_t channel = 0;
	bool chanBl = true;
	bool play = false;
	shared_mutex sourceMut;
	void pass(uint16_t s);
	void func(uint16_t s);
	void soundF(screenObjS& p);
	void serverIO(bool s);
	void statF(bool s, uint8_t a);
	void connectF(uint8_t a);
	char* lsPlay;
	int8_t lsNoPlay;
};

