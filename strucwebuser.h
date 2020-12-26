#pragma once
#include <map>
#include <iostream>

using namespace std;

class clswbusr {
public:
	clswbusr(void);
	~clswbusr(void);
	unsigned int voegid(const unsigned int* usrno);
	void mpupdate(unsigned __int8 minuut);
	struct clswbusrlogstr {
		char* usr;
		unsigned __int8* usrlen;
		char* psw;
		unsigned __int8* pswlen;
	};
	struct strloghost {
		const unsigned int* usrno;
		unsigned __int8* tijd;
	};
	map<unsigned int, clswbusrlogstr*> mpusr;
	map<unsigned int, strloghost*> mphost;
private:
	bool vergminuut(unsigned __int8 x, unsigned __int8 y);
};