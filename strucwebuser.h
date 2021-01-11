#pragma once
#include <stdint.h>
#include <map>
#include <iostream>
#include "Custom/custom_string.h"

using namespace std;

class clswbusr {
public:
	clswbusr(void);
	~clswbusr(void);
	unsigned int voegid(const unsigned int* usrno);
	void mpupdate(uint8_t minuut);
	struct clswbusrlogstr {
		char* usr;
		uint8_t* usrlen;
		char* psw;
		uint8_t* pswlen;
	};
	struct strloghost {
		const unsigned int* usrno;
		uint8_t* tijd;
	};
	map<unsigned int, clswbusrlogstr*> mpusr;
	map<unsigned int, strloghost*> mphost;
private:
	bool vergminuut(uint8_t x, uint8_t y);
};