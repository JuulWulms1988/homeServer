#pragma once
#include "ThreadCls.h"

extern mainThreadCls::radioStr& radioS;

class mainThreadCls::radioStr {
public:
	void open();
	shared_mutex varMut;
	uint8_t chan = 0;
	uint8_t chanCnt = 0;
	char*  getF(char* x);
	void pass(uint16_t x, uint8_t ad);
private:
	struct passStatStr;
	bool play = false;
	mutex passMut[100];
	void func(uint16_t x);
	void playF(uint8_t x, uint8_t old);
	void playPrep(uint8_t x, uint8_t old);
	mutex threadMut;
	strMpCha passMpCha;
	strMpCha MpCha;
	strStrCnt* strS;
	static void connSoundPiF(bool x);
	strMpCh sendMpCh[100];
	passStatStr* passStatS;
};

struct mainThreadCls::radioStr::passStatStr {
	uint8_t type;
	strMpCha MpCha;
	void pass(uint16_t x);
	void func(uint16_t x);
	char* ls;
	int8_t lsNo = radioS.strS->get(ls);
};