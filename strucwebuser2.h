#pragma once
#include <stdint.h>
#include <map>
#include <shared_mutex>
#include <iostream>
#include "Custom/custom_string.h"

using namespace std;
#define WEBUSR_CNT 2


class clswbusr2 {
public:
	clswbusr2(void);
	~clswbusr2(void);
	unsigned int voegid(unsigned int usrno);
	bool getId(unsigned int id, unsigned int& logId, bool& wId);
	mutex mut;
	void mpupdate(uint8_t minuut);
	struct clswbusrlogstr {
		char* usr;
		uint8_t* usrlen;
		char* psw;
		uint8_t* pswlen;
	};
	struct strloghost {
		const unsigned int usrno;
		uint8_t tijd[4];
	};
	map<unsigned int, clswbusrlogstr*> mpusr;
	map<unsigned int, strloghost> mphost;

	struct userIdStr {
		unsigned int id[WEBUSR_CNT][2];
		uint8_t tijd[WEBUSR_CNT][2];
		unsigned int newIdF();
	} usrId;
private:
	bool vergminuut(bool z, uint8_t x, uint8_t y);
	
};