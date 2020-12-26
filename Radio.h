#pragma once
#include "ThreadCls.h"

extern mainThreadCls::radioStr& radioS;

class mainThreadCls::radioStr {
public:
	void open();
	shared_mutex varMut;
	unsigned __int8 chan = 0;
	unsigned __int8 chanCnt = 0;
	char*  getF(char* x);
	void pass(unsigned __int16 x, unsigned __int8 ad);
private:
	struct passStatStr;
	bool play = false;
	mutex passMut[100];
	void func(unsigned __int16 x);
	void playF(unsigned __int8 x, unsigned __int8 old);
	void playPrep(unsigned __int8 x, unsigned __int8 old);
	mutex threadMut;
	strMpCha passMpCha;
	strMpCha MpCha;
	strStrCnt* strS;
	static void connSoundPiF(bool x);
	strMpCh sendMpCh[100];
	passStatStr* passStatS;
};

struct mainThreadCls::radioStr::passStatStr {
	unsigned __int8 type;
	strMpCha MpCha;
	void pass(unsigned __int16 x);
	void func(unsigned __int16 x);
	char* ls;
	__int8 lsNo = radioS.strS->get(ls);
};