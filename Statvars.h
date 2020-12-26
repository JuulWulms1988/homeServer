#pragma once
#include <iostream>
#include <map>
#include <atomic>
using namespace std;

extern unsigned __int8 percatdimaant[10];
extern unsigned __int8 cataant;

class statvars {
public:
	statvars(void);
	~statvars(void);
	struct strtemp {
		atomic<__int8> temp;
		unsigned __int8* client;
	};
	map<unsigned int, char*> mpdimcat;
	unsigned __int8 tempCnt;
	map<unsigned __int8, strtemp*> mptemp;
private:
};
//struct destatvars {
	
//	std::map<unsigned int, strdimvar> mapdimvars;
//};
//struct strdimvar {
//	__int8 aant;
	//bool type[1] = { 0 };
	//unsigned __int8 dimwaarde;
//};