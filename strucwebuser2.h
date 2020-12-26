#pragma once
#include <map>
#include <shared_mutex>
#include <iostream>

using namespace std;
#define WEBUSR_CNT 2


class clswbusr2 {
public:
	clswbusr2(void);
	~clswbusr2(void);
	unsigned int voegid(unsigned int usrno);
	bool getId(unsigned int id, unsigned int& logId, bool& wId);
	mutex mut;
	void mpupdate(unsigned __int8 minuut);
	struct clswbusrlogstr {
		char* usr;
		unsigned __int8* usrlen;
		char* psw;
		unsigned __int8* pswlen;
	};
	struct strloghost {
		const unsigned int usrno;
		unsigned __int8 tijd[4];
	};
	map<unsigned int, clswbusrlogstr*> mpusr;
	map<unsigned int, strloghost> mphost;

	struct userIdStr {
		unsigned int id[WEBUSR_CNT][2];
		unsigned __int8 tijd[WEBUSR_CNT][2];
		unsigned int newIdF();
	} usrId;
private:
	bool vergminuut(bool z, unsigned __int8 x, unsigned __int8 y);
	
};